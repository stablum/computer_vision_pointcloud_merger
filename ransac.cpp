#include "definitions.h"

pcl::CorrespondencesPtr
determine_inliers ( 
    pcl::CorrespondencesPtr all_correspondences,
    pcl::PointCloud < POINT_TYPE >::Ptr keypoints_input,
    pcl::PointCloud < POINT_TYPE >::Ptr keypoints_target
)
{
    pcl::CorrespondencesPtr ret(new pcl::Correspondences);

	pcl::registration::CorrespondenceRejectorSampleConsensus<POINT_TYPE> crsac;
	crsac.setInputCloud(keypoints_input);
	crsac.setTargetCloud(keypoints_target);
	crsac.setMaxIterations(1000);
	crsac.setInputCorrespondences(all_correspondences);
	crsac.getCorrespondences(*ret);
    return ret;
}
