#include <iostream>
#include <pcl/console/parse.h>
#include <pcl/console/print.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/keypoints/iss_3d.h>
#include "definitions.h"

using namespace std;
pcl::PointCloud < POINT_TYPE >::Ptr
detect_keypoints(pcl::PointCloud < POINT_TYPE >::Ptr cloud)
{

//
//  ISS3D parameters
//
    double iss_salient_radius_;
    double iss_non_max_radius_;
    double iss_gamma_21_(0.975);
    double iss_gamma_32_(0.975);
    double iss_min_neighbors_(10);
    int iss_threads_(8);

    pcl::PointCloud <
        POINT_TYPE >::Ptr ret(new pcl::PointCloud <
                                          POINT_TYPE > ());
    pcl::search::KdTree < POINT_TYPE >::Ptr tree(new pcl::search::KdTree <
                                                 POINT_TYPE > ());

// Fill in the model cloud

    double model_resolution = 0.001;

// Compute model_resolution

    iss_salient_radius_ = 6 * model_resolution;
    iss_non_max_radius_ = 4 * model_resolution;

//
// Compute keypoints
//
    pcl::ISSKeypoint3D < POINT_TYPE, POINT_TYPE > iss_detector;

    iss_detector.setSearchMethod(tree);
    iss_detector.setSalientRadius(iss_salient_radius_);
    iss_detector.setNonMaxRadius(iss_non_max_radius_);
    iss_detector.setThreshold21(iss_gamma_21_);
    iss_detector.setThreshold32(iss_gamma_32_);
    iss_detector.setMinNeighbors(iss_min_neighbors_);
    iss_detector.setNumberOfThreads(iss_threads_);
    iss_detector.setInputCloud(cloud);
    iss_detector.compute(*ret);

    return ret;
}
