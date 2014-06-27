#include "definitions.h"

using namespace std;

pcl::PointCloud < POINT_TYPE >::Ptr
flipyz (
    pcl::PointCloud < POINT_TYPE >::Ptr in
) {
    pcl::PointCloud < POINT_TYPE >::Ptr ret(new pcl::PointCloud < POINT_TYPE >);

    pcl::copyPointCloud(*in, *ret);

    for (size_t i = 0; i < ret->points.size (); ++i) {
        ret->points[i].z = - ret->points[i].z;
        ret->points[i].y = - ret->points[i].y;
    }

    return ret;
}

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
   //keypoints1 = flipyz(keypoints1);
   //keypoints2 = flipyz(keypoints2);

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
   viewer.setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "cloud1");
   viewer.addPointCloud<POINT_TYPE> (cloud2, cloud2_color_handler, "cloud2");
   viewer.setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "cloud2");

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

void
show_normals (
        pcl::PointCloud<POINT_TYPE>::ConstPtr cloud,
        pcl::PointCloud<pcl::Normal>::ConstPtr normals
)
{
	// Visualization of keypoints along with the original cloud
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("Normals Viewer"));
	pcl::visualization::PointCloudColorHandlerRGBField<POINT_TYPE> cloud_color_handler(cloud);
	viewer->setBackgroundColor( 0.1, 0.1, 0.1 );
	viewer->addPointCloud(cloud, cloud_color_handler, "cloud");
	viewer->addPointCloudNormals<POINT_TYPE, pcl::Normal>(cloud, normals, 10, 0.02, "normals");
   while (!viewer->wasStopped ())
   {
      viewer->spinOnce();
   }
}

void
show_merged (
    pcl::PointCloud<POINT_TYPE>::Ptr cloud1,
    pcl::PointCloud<POINT_TYPE>::Ptr cloud2
)
 {
   //... populate cloud
   pcl::visualization::PCLVisualizer viewer ("3D Viewer");

   viewer.setBackgroundColor(0.5, 0.5, 0.5);

   pcl::visualization::PointCloudColorHandlerRGBField<POINT_TYPE> cloud_color_handler1(cloud1);
   pcl::visualization::PointCloudColorHandlerRGBField<POINT_TYPE> cloud_color_handler2(cloud2);

   viewer.addPointCloud<POINT_TYPE> (cloud1, cloud_color_handler1, "cloud1");
   viewer.addPointCloud<POINT_TYPE> (cloud2, cloud_color_handler2, "cloud2");

   while (!viewer.wasStopped ())
   {
      viewer.spinOnce();
   }
 }
