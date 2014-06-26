#include "definitions.h"

using namespace std;

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

        std::cout << "After downsampling: " << clouds[seq]->points.size()
            << " data points" << std::endl;

        keypoints_sets[seq] = detect_keypoints(clouds[seq]);

        features_sets[seq] = calculate_feature_descriptors(clouds[seq], normals, keypoints_sets[seq]);

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
    
    pcl::CorrespondencesPtr all_correspondences
    	= determine_correspondences(features_sets[0],features_sets[1]);
    
   	cout << "No. of all correspondences: " <<  all_correspondences->size() << endl;

    pcl::CorrespondencesPtr inlier_correspondences
    	= determine_inliers(all_correspondences, keypoints_sets[0], keypoints_sets[1]);
    	
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
