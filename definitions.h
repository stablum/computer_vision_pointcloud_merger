#include <iostream>
#include <pcl/console/parse.h>
#include <pcl/console/print.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/keypoints/iss_3d.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/filters/voxel_grid.h>

#define BORDER_ESTIMATION 1

//define POINT_TYPE pcl::PointXYZRGBNormal
#define POINT_TYPE pcl::PointXYZRGB
//define POINT_TYPE pcl::PointXYZ

#define NUM_KINECTS 2

pcl::PointCloud < POINT_TYPE >::Ptr
detect_keypoints(pcl::PointCloud < POINT_TYPE >::Ptr cloud);

void
show_cloud (
    pcl::PointCloud<POINT_TYPE>::Ptr cloud,
    pcl::PointCloud<POINT_TYPE>::Ptr keypoints
);

pcl::PointCloud<POINT_TYPE>::Ptr
	downsample (pcl::PointCloud<POINT_TYPE>::Ptr cloud, float leafsize);

