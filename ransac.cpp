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
    crsac.setInlierThreshold(CRSAC_INLIER_TRESHOLD);
	crsac.setInputCloud(keypoints_input);
	crsac.setTargetCloud(keypoints_target);
	crsac.setMaxIterations(CRSAC_MAX_ITERATIONS);
	crsac.setInputCorrespondences(all_correspondences);
	crsac.getCorrespondences(*ret);
    crsac.getRemainingCorrespondences(*all_correspondences, *ret);

    std::cout << "crsac inlier treshold:" << crsac.getInlierThreshold () << std::endl;
    return ret;
}
