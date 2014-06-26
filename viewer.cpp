#include "definitions.h"

using namespace std;

void
show_cloud (
    pcl::PointCloud<POINT_TYPE>::Ptr cloud,
    pcl::PointCloud<POINT_TYPE>::Ptr keypoints
)
 {

   //... populate cloud
   pcl::visualization::PCLVisualizer viewer ("3D Viewer");

   viewer.setBackgroundColor(0.5, 0.5, 0.5);

   pcl::visualization::PointCloudColorHandlerCustom<POINT_TYPE> keypoints_color_handler (keypoints, 0, 255, 0);
   pcl::visualization::PointCloudColorHandlerRGBField<POINT_TYPE> cloud_color_handler(cloud);

   viewer.addPointCloud<POINT_TYPE> (keypoints, keypoints_color_handler, "keypoints");
   viewer.setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 7, "keypoints");

   viewer.addPointCloud<POINT_TYPE> (cloud, cloud_color_handler, "cloud");

   while (!viewer.wasStopped ())
   {
      viewer.spinOnce();
   }
 }


void
show_correspondences (
    pcl::PointCloud<POINT_TYPE>::Ptr cloud1,
    pcl::PointCloud<POINT_TYPE>::Ptr cloud2,
    pcl::PointCloud<POINT_TYPE>::Ptr keypoints1,
    pcl::PointCloud<POINT_TYPE>::Ptr keypoints2,
    pcl::CorrespondencesPtr correspondences
)
 {

   //... populate cloud
   pcl::visualization::PCLVisualizer viewer ("3D Viewer for correspondences");

   viewer.setBackgroundColor(0.5, 0.5, 0.5);

   pcl::visualization::PointCloudColorHandlerCustom<POINT_TYPE> keypoints1_color_handler (keypoints1, 0, 255, 0);
   pcl::visualization::PointCloudColorHandlerCustom<POINT_TYPE> keypoints2_color_handler (keypoints2, 255, 0, 0);

   pcl::visualization::PointCloudColorHandlerRGBField<POINT_TYPE> cloud1_color_handler(cloud1);
   pcl::visualization::PointCloudColorHandlerRGBField<POINT_TYPE> cloud2_color_handler(cloud2);

   viewer.addPointCloud<POINT_TYPE> (keypoints1, keypoints1_color_handler, "keypoints1");
   viewer.setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "keypoints1");

   viewer.addPointCloud<POINT_TYPE> (keypoints2, keypoints2_color_handler, "keypoints2");
   viewer.setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "keypoints2");

   viewer.addPointCloud<POINT_TYPE> (cloud1, cloud1_color_handler, "cloud1");
   viewer.addPointCloud<POINT_TYPE> (cloud2, cloud2_color_handler, "cloud2");

    for (size_t i = 0; i < correspondences->size(); i++) {
		const POINT_TYPE &p_src = keypoints2->points[(*correspondences)[i].index_query];
		const POINT_TYPE &p_tgt = keypoints1->points[(*correspondences)[i].index_match];
		std::stringstream ss("line");
		ss << i;
		viewer.addLine(p_src, p_tgt, 1, 1, 1, ss.str());
	}

   while (!viewer.wasStopped ())
   {
      viewer.spinOnce();
   }
 }
