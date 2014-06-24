#include <stdio.h>
#include <windows.h>
#include <pthread.h>
#include <iostream>
#include <cstdlib>

#include <ntk/camera/openni_grabber.h>
#include <ntk/mesh/mesh_generator.h>

using namespace std;
using namespace ntk;

#define NUM_KINECTS 2

struct CurrFrame {
    bool processed;
    RGBDImage image;
};

CurrFrame curr_frames[NUM_KINECTS];
pthread_mutex_t access_frame_mutexes[NUM_KINECTS];

OpenniDriver ni_driver;

void lock(int kinectid)
{
    pthread_mutex_lock(&(access_frame_mutexes[kinectid]));
    //cout << ">>> mutex " << kinectid << " locked" << endl;
}

void unlock(int kinectid)
{
    pthread_mutex_unlock(&(access_frame_mutexes[kinectid]));
    //cout << "<<< mutex " << kinectid << " unlocked" << endl;
}

void *kinect_reader(void *threadid)
{
    long tid;
    int count = 0;
    tid = (long) threadid;
    cout << "Thread for kinect reader n. " << tid << " started" << endl;


    int num_dev = ni_driver.numDevices();

#if 1
    if (num_dev < NUM_KINECTS) {
	{
	    while (true) {
		Sleep(1000);
		cout << "Error: Less than two Kinect were detected (" <<
		    ni_driver.numDevices() << ") for tid:" << tid << endl;
	    }
	}
    }
#endif

    OpenniGrabber *grabber = new OpenniGrabber(ni_driver, 0);

    grabber->setTrackUsers(false);
    grabber->connectToDevice();
    grabber->start();

    cout << "Before mesh generator" << endl;
    // Mesh generator
    MeshGenerator *mesh_generator = new MeshGenerator();
    mesh_generator->setMeshType(MeshGenerator::PointCloudMesh);

    RGBDImage image;
    while (true) {
	count++;
	grabber->waitForNextFrame();
	cout << "!" << tid;
	lock(tid);
	// got the frame
	grabber->copyImageTo(curr_frames[tid].image);
	curr_frames[tid].processed = false;
	unlock(tid);
    }
}

void process_frame(int kinectid, RGBDImage frame_data)
{
    cout << "processing frame from kinect " << kinectid << endl;
}

RGBDImage get_frame(int kinectid)
{
    cout << "get frame " << kinectid << endl;
    curr_frames[kinectid].processed = true;	// will skip (and not process) this frame next time
    RGBDImage ret = curr_frames[kinectid].image;
    //curr_frames[kinectid].image = 0; // empty it
    return ret;
}

void poll_kinect_statuses()
{
    cout << "checking kinect statuses.." << endl;
    int i;
    for (i = 0; i < NUM_KINECTS; i++) {
	lock(i);
	if (curr_frames[i].processed == false) {
	    cout << "found frame not processed for kinect n." << i << endl;
	    RGBDImage frame_data = get_frame(i);
	    unlock(i);
	    process_frame(i, frame_data);
	} else {
	    unlock(i);
	}
    }
    cout << "ended checking kinect statuses" << endl;
}

int main(int argc, const char *argv[])
{
    pthread_t threads[NUM_KINECTS];
    int rc;
    int i;
    for (i = 0; i < NUM_KINECTS; i++) {
	pthread_mutex_init(&(access_frame_mutexes[i]), NULL);
	curr_frames[i].processed = true;
	//curr_frames[i].image = -2;
	cout << "main() : creating thread, " << i << endl;
	rc = pthread_create(&threads[i], NULL, kinect_reader, (void *) i);
	if (rc) {
	    while (true) {
		Sleep(1000);
		cout << "Error: unable to create thread," << rc << endl;
	    }
	}
    }

    while (true) {
	Sleep(1000);
	poll_kinect_statuses();
    }

    pthread_exit(NULL);
}
