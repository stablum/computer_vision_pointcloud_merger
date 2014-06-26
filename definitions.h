#include <iostream>
#include <pcl/console/parse.h>
#include <pcl/console/print.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/keypoints/iss_3d.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/features/fpfh.h>
#include <pcl/registration/correspondence_estimation.h>
#include <pcl/registration/correspondence_rejection_sample_consensus.h>

#define BORDER_ESTIMATION 1

//define POINT_TYPE pcl::PointXYZRGBNormal
#define POINT_TYPE pcl::PointXYZRGB
//define POINT_TYPE pcl::PointXYZ

#define NUM_KINECTS 2
//define DOWNSAMPLE_LEAFSIZE 0.04f
#define DOWNSAMPLE_LEAFSIZE 0.01f

pcl::PointCloud < POINT_TYPE >::Ptr
detect_keypoints(pcl::PointCloud < POINT_TYPE >::Ptr cloud);

void
show_cloud (
    pcl::PointCloud<POINT_TYPE>::Ptr cloud,
    pcl::PointCloud<POINT_TYPE>::Ptr keypoints
);

pcl::PointCloud<POINT_TYPE>::Ptr
	downsample (pcl::PointCloud<POINT_TYPE>::Ptr cloud, float leafsize);

pcl::PointCloud<pcl::Normal>::Ptr
calculate_normals(pcl::PointCloud<POINT_TYPE>::Ptr cloud);

pcl::PointCloud<pcl::FPFHSignature33>::Ptr calculate_feature_descriptors(pcl::PointCloud<POINT_TYPE>::Ptr cloud, pcl::PointCloud<pcl::Normal>::Ptr normals, pcl::PointCloud<POINT_TYPE>::Ptr keypoints);

pcl::CorrespondencesPtr
determine_correspondences(
    pcl::PointCloud < pcl::FPFHSignature33 >::Ptr fpfhs1,
    pcl::PointCloud < pcl::FPFHSignature33 >::Ptr fpfhs2
);

pcl::CorrespondencesPtr
determine_inliers ( 
    pcl::CorrespondencesPtr all_correspondences,
    pcl::PointCloud < POINT_TYPE >::Ptr keypoints_input,
    pcl::PointCloud < POINT_TYPE >::Ptr keypoints_target
);

void
show_correspondences (
    pcl::PointCloud<POINT_TYPE>::Ptr cloud1,
    pcl::PointCloud<POINT_TYPE>::Ptr cloud2,
    pcl::PointCloud<POINT_TYPE>::Ptr keypoints1,
    pcl::PointCloud<POINT_TYPE>::Ptr keypoints2,
    pcl::CorrespondencesPtr correspondences
);

