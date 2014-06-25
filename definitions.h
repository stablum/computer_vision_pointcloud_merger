//define POINT_TYPE pcl::PointXYZRGBNormal
#define POINT_TYPE pcl::PointXYZRGBA

pcl::PointCloud < POINT_TYPE >::Ptr
detect_keypoints(pcl::PointCloud < POINT_TYPE >::Ptr cloud);

