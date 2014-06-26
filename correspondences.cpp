#include "definitions.h"


pcl::CorrespondencesPtr
determine_correspondences(
    pcl::PointCloud < pcl::FPFHSignature33 >::Ptr fpfhs1,
    pcl::PointCloud < pcl::FPFHSignature33 >::Ptr fpfhs2
)
{
    pcl::CorrespondencesPtr all_correspondences(new pcl::Correspondences);
    pcl::registration::CorrespondenceEstimation < pcl::FPFHSignature33, pcl::FPFHSignature33 > est;
    est.setInputCloud(fpfhs2);
    est.setInputTarget(fpfhs1);
    est.determineReciprocalCorrespondences(*all_correspondences);
    return all_correspondences;
}
