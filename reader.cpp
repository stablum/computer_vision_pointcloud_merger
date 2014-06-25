#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
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

    int frame_id;
    for (frame_id = 0; frame_id <= 99; frame_id++) {
        int seq;
        for (seq = 1; seq <= 2; seq++) {
            cloud = read_cloud(1, frame_id);
            std::cout << "Loaded "
                << cloud->width * cloud->height
                << " data points from point cloud, seq="
                << seq << " frame_id=" << frame_id
                << std::endl;

            pcl::PointCloud < POINT_TYPE >::Ptr keypoints =
                detect_keypoints(cloud);
            cout << "number of keypoints:" << keypoints->points.size() << endl;
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
