#include "definitions.h"

struct CorrespondencesStuff {
    pcl::CorrespondencesPtr correspondences,
    pcl::registration::CorrespondenceEstimation::Ptr < pcl::FPFHSignature33, pcl::FPFHSignature33 > est
};

CorrespondencesStuff *
determine_correspondences(
    pcl::PointCloud < pcl::FPFHSignature33 >::Ptr fpfhs1,
    pcl::PointCloud < pcl::FPFHSignature33 >::Ptr fpfhs2
)
{
    CorrespondencesStuff * ret = malloc(sizeof(*ret));

    pcl::CorrespondencesPtr all_correspondences(new pcl::Correspondences);
    pcl::registration::CorrespondenceEstimation::Ptr < pcl::FPFHSignature33, pcl::FPFHSignature33 > est(new pcl::registration::CorrespondenceEstimation::Ptr < pcl::FPFHSignature33, pcl::FPFHSignature33 >);
    est->setInputCloud(fpfhs2);
    est->setInputTarget(fpfhs1);
#ifdef RECIPROCAL_CORRESPONDENCES
    est->determineReciprocalCorrespondences(*all_correspondences);
#else
    est->determineCorrespondences(*all_correspondences);
#endif
    
    ret->correspondences = all_correspondences;
    ret->est = est;

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

