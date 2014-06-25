#include "definitions.h"

pcl::PointCloud<POINT_TYPE>::Ptr
	downsample (pcl::PointCloud<POINT_TYPE>::Ptr cloud, float leafsize)
{
	// Create the filtering object
	pcl::VoxelGrid<POINT_TYPE> sor;
	pcl::PointCloud<POINT_TYPE>::Ptr cloud_filtered(new pcl::PointCloud<POINT_TYPE>());
	sor.setInputCloud (cloud);
	sor.setLeafSize (leafsize, leafsize, leafsize);
	sor.filter (*cloud_filtered);

	std::cerr << "PointCloud after filtering: " << cloud_filtered->width * cloud_filtered->height 
		<< " data points (" << pcl::getFieldsList (*cloud_filtered) << ").";
	return cloud_filtered;
}

