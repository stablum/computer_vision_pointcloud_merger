#include "definitions.h"

pcl::PointCloud < POINT_TYPE >::Ptr
select_keypoints (
    pcl::PointCloud < POINT_TYPE >::Ptr keypoints
)
{
    pcl::PointCloud < POINT_TYPE >::Ptr ret (new pcl::PointCloud <POINT_TYPE>); 
    ret->clear(); // just to be sure

    for(int i = 0; i < keypoints->points.size(); i++) {
        double z = keypoints->points[i].z;
        if(abs(z) < FILTER_Z_TRESHOLD) {
            ret->push_back(keypoints->points[i]);
            std::cout << "point kept" << i << "" << z << endl;
        } else {
            std::cout << "removed" << i << " " << z << endl;
        }
    }
    return ret;
}

using namespace std;
pcl::PointCloud < POINT_TYPE >::Ptr
detect_keypoints(pcl::PointCloud < POINT_TYPE >::Ptr cloud)
{

//
//  ISS3D parameters
//
    double iss_salient_radius_;
    double iss_non_max_radius_;
#ifdef BORDER_ESTIMATION
    double iss_normal_radius_;
    double iss_border_radius_;
#endif
    double iss_gamma_21_(0.990);
    double iss_gamma_32_(0.990);
    double iss_min_neighbors_(ISS_MIN_NEIGHBORS);
    int iss_threads_(4);

    pcl::PointCloud <
        POINT_TYPE >::Ptr ret(new pcl::PointCloud <
                                          POINT_TYPE > ());
    pcl::search::KdTree < POINT_TYPE >::Ptr tree(new pcl::search::KdTree <
                                                 POINT_TYPE > ());

// Fill in the model cloud

    double model_resolution = 0.01;

// Compute model_resolution

    iss_salient_radius_ = 18 * model_resolution;
    iss_non_max_radius_ = 4 * model_resolution;

#ifdef BORDER_ESTIMATION
    iss_normal_radius_ = 4 * model_resolution;
    iss_border_radius_ = 1 * model_resolution;
#endif

//
// Compute keypoints
//
    pcl::ISSKeypoint3D < POINT_TYPE, POINT_TYPE > iss_detector;

    iss_detector.setSearchMethod(tree);
    iss_detector.setSalientRadius(iss_salient_radius_);
    iss_detector.setNonMaxRadius(iss_non_max_radius_);

#ifdef BORDER_ESTIMATION
    iss_detector.setNormalRadius(iss_normal_radius_);
    iss_detector.setBorderRadius(iss_border_radius_);
#endif

    iss_detector.setThreshold21(iss_gamma_21_);
    iss_detector.setThreshold32(iss_gamma_32_);
    iss_detector.setMinNeighbors(iss_min_neighbors_);
    iss_detector.setNumberOfThreads(iss_threads_);
    iss_detector.setInputCloud(cloud);
    iss_detector.compute(*ret);
    ret = select_keypoints(ret);
    return ret;
}
