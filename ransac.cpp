#include "definitions.h"

extern float crsac_inlier_treshold;

Eigen::Matrix4f
determine_inliers (
    pcl::CorrespondencesPtr inliers,
    pcl::CorrespondencesPtr all_correspondences,
    pcl::PointCloud < POINT_TYPE >::Ptr keypoints_input,
    pcl::PointCloud < POINT_TYPE >::Ptr keypoints_target
)
{

	pcl::registration::CorrespondenceRejectorSampleConsensus<POINT_TYPE> crsac;
    crsac.setInlierThreshold(crsac_inlier_treshold);
	crsac.setInputCloud(keypoints_input);
	crsac.setTargetCloud(keypoints_target);
	crsac.setMaxIterations(CRSAC_MAX_ITERATIONS);
	crsac.setInputCorrespondences(all_correspondences);
	crsac.getCorrespondences(*inliers);
    crsac.getRemainingCorrespondences(*all_correspondences, *inliers);
    std::cout << "crsac inlier treshold:" << crsac.getInlierThreshold () << std::endl;
    return crsac.getBestTransformation();
}
