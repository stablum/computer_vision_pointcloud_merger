#include "definitions.h"

pcl::PointCloud<pcl::FPFHSignature33>::Ptr calculate_feature_descriptors(
    pcl::PointCloud<POINT_TYPE>::Ptr cloud,
    pcl::PointCloud<pcl::Normal>::Ptr normals,
    pcl::PointCloud<POINT_TYPE>::Ptr keypoints)
{
	// Create a PFHEstimation object
	pcl::FPFHEstimation<POINT_TYPE, pcl::Normal, pcl::FPFHSignature33> fpfh;

	// Convert the keypoints cloud from PointWithScale to PointXYZ
	// so that it will be compatible with our original point cloud
	printf("before copyPointCloud\n");
// 	pcl::PointCloud<pcl::PointXYZ>::Ptr keypoints_xyz(new pcl::PointCloud<pcl::PointXYZ>());
// 	copyPointCloud(*keypoints, *keypoints_xyz);
// 	printf("Number of keypoints: %i\n", keypoints->size());
// 	printf("Number of keypoints_xyz: %i\n", keypoints_xyz->size());

	// Use all of the points for analyzing the local structure of the cloud
	printf("before set surface and normals\n");
	printf("Num of points: %i\n", cloud->points.size());
	fpfh.setSearchSurface(cloud);
	printf("Num of normals: %i\n", normals->points.size());
	fpfh.setInputNormals(normals);

	// Only compute features at the keypoints
	// 	printf("before set keypoints.\n");
	fpfh.setInputCloud(keypoints);

	// Set it to use a KdTree to perform its neighborhood searches
	pcl::search::KdTree<POINT_TYPE>::Ptr tree(new pcl::search::KdTree<POINT_TYPE>());
	printf("before set KdTree\n");
	fpfh.setSearchMethod(tree);

	// Use all neighbors in a sphere of radius 5cm
	// IMPORTANT: the radius used here has to be larger than the radius used to estimate the surface normals!!!
	printf("before set Radius\n");
	fpfh.setRadiusSearch (0.05);

	// Output datasets
	pcl::PointCloud<pcl::FPFHSignature33>::Ptr fpfhs(new pcl::PointCloud<pcl::FPFHSignature33>());

	// Compute the features
	fpfh.compute(*fpfhs);

	return fpfhs;
}

