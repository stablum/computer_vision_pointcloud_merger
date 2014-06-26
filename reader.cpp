#include "definitions.h"

using namespace std;

void
print_correspondences_and_histograms(
    pcl::CorrespondencesPtr correspondences,
    pcl::PointCloud<pcl::FPFHSignature33>::Ptr features1,
    pcl::PointCloud<pcl::FPFHSignature33>::Ptr features2
)
{
    for (size_t i = 0; i < correspondences->size(); i++) {
        int q = (*correspondences)[i].index_query;
        int m = (*correspondences)[i].index_match;

		std::cout << "!for correspondence n." << i 
            << " index_query=" << q
            << " index_match=" << m
            << endl;
        cout << "!!1!!";
        print_feature_descriptor(features1->points[q]);
        cout << "!!2!!";
        print_feature_descriptor(features2->points[q]);
    }
}


pcl::PointCloud < POINT_TYPE >::Ptr read_cloud(int sequence_nr,
                                               int frame_id)
{
    char filename[100];
    pcl::PointCloud < POINT_TYPE >::Ptr cloud(new pcl::PointCloud <
                                              POINT_TYPE >);
    // IMPORTANT: the following + 1 is because the folders are named from 1 and not from 0
    sprintf(filename, "sequence%d/%03d.pcd", sequence_nr + 1, frame_id);
    cout << "the filename is: " << filename << endl;
    if (pcl::io::loadPCDFile < POINT_TYPE > (filename, *cloud) == -1)   //* load the file
    {
        cout << "Couldn't read file " << filename << endl;
        exit(-1);
    }

#ifdef FLIPYZ
    for (size_t i = 0; i < cloud->points.size (); ++i) {
        cloud->points[i].z = - cloud->points[i].z;
        cloud->points[i].y = - cloud->points[i].y;
    }
#endif

    return cloud;
}

void load_and_process_instant(int frame_id)
{

    pcl::PointCloud < POINT_TYPE >::Ptr keypoints_sets[NUM_KINECTS];
    pcl::PointCloud<pcl::FPFHSignature33>::Ptr features_sets[NUM_KINECTS];
    pcl::PointCloud < POINT_TYPE >::Ptr clouds[NUM_KINECTS];
    
    int seq;
    for (seq = 0; seq < NUM_KINECTS; seq++) {

        pcl::PointCloud<pcl::Normal>::Ptr normals;

        clouds[seq] = read_cloud(seq, frame_id);
        std::cout << "Loaded " << clouds[seq]->points.size()
            << " data points from point cloud, seq="
            << seq << " frame_id=" << frame_id << std::endl;
    
        clouds[seq] = downsample(clouds[seq], DOWNSAMPLE_LEAFSIZE);

        normals = calculate_normals(clouds[seq]);
        //show_normals(clouds[seq],normals);

        std::cout << "After downsampling: " << clouds[seq]->points.size()
            << " data points" << std::endl;

        std::cout << "detecting keypoints...";
        keypoints_sets[seq] = detect_keypoints(clouds[seq]);
        std::cout << "done." << std::endl;

        std::cout << "calculating feature descriptors...";
        features_sets[seq] = calculate_feature_descriptors(clouds[seq], normals, keypoints_sets[seq]);
        std::cout << "done." << std::endl;

        cout << "number of keypoints:" << keypoints_sets[seq]->points.
            size() << endl;
        //show_cloud(clouds[seq], keypoints_sets[seq]);
        /*
           for (size_t i = 0; i < cloud->points.size (); ++i)
           std::cout << "    " << cloud->points[i].x
           << " "    << cloud->points[i].y
           << " "    << cloud->points[i].z << std::endl;
         */
    }
    
    std::cout << "determining correspondences...";
    pcl::CorrespondencesPtr all_correspondences
    	= determine_correspondences(features_sets[0],features_sets[1]);
    std::cout << "done." << std::endl;
    
   	cout << "No. of all correspondences: " <<  all_correspondences->size() << endl;

    print_correspondences_indexes(all_correspondences);

    print_correspondences_and_histograms(all_correspondences,features_sets[0],features_sets[1]);

    std::cout << "determining inliers...";
    pcl::CorrespondencesPtr inlier_correspondences
    	= determine_inliers(all_correspondences, keypoints_sets[0], keypoints_sets[1]);
    std::cout << "done." << std::endl;
    	
   	cout << "No. of inlier correspondences: " <<  inlier_correspondences->size() << endl;
    
    show_correspondences(clouds[0], clouds[1], keypoints_sets[0], keypoints_sets[1], all_correspondences);
    show_correspondences(clouds[0], clouds[1], keypoints_sets[0], keypoints_sets[1], inlier_correspondences);

}

int main(int argc, char **argv)
{

    int frame_id;
    for (frame_id = 0; frame_id <= 99; frame_id++) {
        load_and_process_instant(frame_id);
    }

    return (0);
}
