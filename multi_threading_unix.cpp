#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <cstdlib>
 
using namespace std;

#define NUM_KINECTS 2

struct CurrFrame {
	bool processed;
	int payload;
};

CurrFrame curr_frames[NUM_KINECTS];
pthread_mutex_t access_frame_mutex;

void *kinect_reader(void *threadid)
{
   long tid;
   int count = 0;
   tid = (long)threadid;
   cout << "Thread for kinect reader n. " << tid << " started" << endl;
   while(true) {
   	   count++;
   	   int waiting_time = 1 + rand() % 10; // max 10 seconds
	   cout << "Thread n. " << tid << " will wait for " << waiting_time << " seconds (before getting the frame)" << endl;
	   sleep(waiting_time);
	   
	   // got the frame
	   pthread_mutex_lock(&access_frame_mutex);
	   curr_frames[tid].processed = false;
	   curr_frames[tid].payload = count;
	   pthread_mutex_unlock(&access_frame_mutex);
   }
}

int process_frame(int kinectid) {
	cout << "processing frame " << kinectid << endl;
	curr_frames[kinectid].processed = true; // will skip (and not process) this frame next time
}

int poll_kinect_statuses()
{
	cout << "checking kinect statuses.." << endl;
	int i;
	for (i = 0; i < NUM_KINECTS; i++) {
		if(curr_frames[i].processed == false) {
			cout << "found frame not processed for kinect n." << i << endl;
			process_frame(i);
		}
	}
	cout << "ended checking kinect statuses" << endl;
}

int main(int argc, const char *argv[])
{
    pthread_t threads[NUM_KINECTS];
    pthread_mutex_init(&access_frame_mutex, NULL);
    int rc;
    int i;
    for (i = 0; i < NUM_KINECTS; i++) {
    	curr_frames[i].processed = false;
    	curr_frames[i].payload = -2;
        cout << "main() : creating thread, " << i << endl;
        rc = pthread_create(&threads[i], NULL, kinect_reader, (void *) i);
		if (rc) {
			cout << "Error: unable to create thread," << rc << endl;
		    exit(-1);
		}
    }
    
    while(true) {
    	sleep(1);
    	pthread_mutex_lock(&access_frame_mutex);
    	poll_kinect_statuses();
    	pthread_mutex_unlock(&access_frame_mutex);
    }
    
    pthread_exit(NULL);
}
