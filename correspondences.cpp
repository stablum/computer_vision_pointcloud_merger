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
    est.determineCorrespondences(*all_correspondences);
    return all_correspondences;
}

void
print_correspondences_indexes(
    pcl::CorrespondencesPtr correspondences
)
{
    for (size_t i = 0; i < correspondences->size(); i++) {
        int q = (*correspondences)[i].index_query;
        int m = (*correspondences)[i].index_match;

		std::cout << "for correspondence n." << i 
            << " index_query=" << q
            << " index_match=" << m
            << endl;
    }
}

