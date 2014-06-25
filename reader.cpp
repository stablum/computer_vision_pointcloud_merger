#include "definitions.h"

using namespace std;

pcl::PointCloud < POINT_TYPE >::Ptr read_cloud(int sequence_nr,
                                               int frame_id)
{
    char filename[100];
    pcl::PointCloud < POINT_TYPE >::Ptr cloud(new pcl::PointCloud <
                                              POINT_TYPE >);
    sprintf(filename, "sequence%d/%03d.pcd", sequence_nr, frame_id);
    cout << "the filename is: " << filename << endl;
    if (pcl::io::loadPCDFile < POINT_TYPE > (filename, *cloud) == -1)   //* load the file
    {
        cout << "Couldn't read file " << filename << endl;
        exit(-1);
    }
    return cloud;
}

int main(int argc, char **argv)
{
    pcl::PointCloud < POINT_TYPE >::Ptr cloud;

    pcl::PointCloud < POINT_TYPE >::Ptr keypoints_sets[NUM_KINECTS];

    int frame_id;
    for (frame_id = 0; frame_id <= 99; frame_id++) {
        int seq;
        for (seq = 0; seq < NUM_KINECTS; seq++) {
            cloud = read_cloud(1, frame_id);
            std::cout << "Loaded "
                << cloud->points.size()
                << " data points from point cloud, seq="
                << seq << " frame_id=" << frame_id
                << std::endl;

            cloud = downsample(cloud,0.04f);
        
            std::cout << "After downsampling: "
                << cloud->points.size()
                << " data points"
                << std::endl;

            keypoints_sets[seq] =
                detect_keypoints(cloud);

            cout << "number of keypoints:" << keypoints_sets[seq]->points.size() << endl;
            show_cloud(cloud,keypoints_sets[seq]);
            show_cloud(cloud,keypoints_sets[seq]);
            /*
               for (size_t i = 0; i < cloud->points.size (); ++i)
               std::cout << "    " << cloud->points[i].x
               << " "    << cloud->points[i].y
               << " "    << cloud->points[i].z << std::endl;
             */
        }
        
    }

    return (0);
}
