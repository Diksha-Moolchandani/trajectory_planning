#include "rrt_star_3d.h"

namespace kamaz {
namespace hagen {

    RRTStar RRTStar3D::rrt_search(SearchSpace search_space, std::vector<Eigen::VectorXd> lengths_of_edges
                , Eigen::VectorXd start_pose, Eigen::VectorXd goal_pose, int _max_samples
                , int resolution, float pro, int _rewrite_count){

        return RRTStar(search_space, lengths_of_edges, start_pose, goal_pose, _max_samples, resolution, pro, _rewrite_count);                   
    }

    Eigen::VectorXd RRTStar3D::get_search_space_dim(Eigen::VectorXd dimensions){
        Eigen::VectorXd dim_(6);
        dim_<< 0, dimensions[0], 0, dimensions[1], 0, dimensions[2];
        return dim_;
    }

    std::vector<SearchSpace::Rect> RRTStar3D::get_obstacles(){
        std::vector<SearchSpace::Rect> _objects;
        _objects.push_back(SearchSpace::Rect(20, 20, 20, 40, 40, 40));
        _objects.push_back(SearchSpace::Rect(20, 20, 60, 40, 40, 80));
        _objects.push_back(SearchSpace::Rect(20, 60, 20, 40, 80, 40));
        _objects.push_back(SearchSpace::Rect(60, 60, 20, 80, 80, 40));
        _objects.push_back(SearchSpace::Rect(60, 20, 20, 80, 40, 40));
        _objects.push_back(SearchSpace::Rect(60, 20, 60, 80, 40, 80));
        _objects.push_back(SearchSpace::Rect(20, 60, 60, 40, 80, 80));
        _objects.push_back(SearchSpace::Rect(60, 60, 60, 80, 80, 80));
        return _objects;
    }

    std::vector<SearchSpace::Rect> RRTStar3D::get_random_obstacles(int number_of_obstacles, Eigen::VectorXd x_dimentions){
        std::vector<SearchSpace::Rect> _objects;
        for(int i=0; i< number_of_obstacles; i++){
            float x = (rand()%(int)x_dimentions[0]);
            float y = (rand()%(int)x_dimentions[1]);
            float z = (rand()%(int)x_dimentions[2]);
            int width_x = x + rand()%20;
            int width_y = y + rand()%20;
            int width_z = z + rand()%20;
            if(width_x >= (int)x_dimentions[0] 
            || width_y >= (int)x_dimentions[1] || width_z >= (int)x_dimentions[2]){
                continue;
            }
            _objects.push_back(SearchSpace::Rect(x, y, z, width_x, width_y, width_z));
        }
        return _objects;
    }

    void RRTStar3D::save_edges(std::map<int, Tree> trees){
       std::vector<float> edges; 
       int count = 0;
       for(auto const&item : trees[0].E){
            // std::cout<< item.second.transpose() << std::endl;
            auto sp = item.first;
            auto ep = item.second;
            edges.push_back(std::get<0>(sp));
            edges.push_back(std::get<1>(sp));
            edges.push_back(std::get<2>(sp));
            edges.push_back(ep[0]);
            edges.push_back(ep[1]);
            edges.push_back(ep[2]);
            count += 1;
        }

        cnpy::npy_save("/dataset/edges.npy",&edges[0],{1, count, 6},"w");
    }

    void RRTStar3D::save_obstacle(std::vector<SearchSpace::Rect> obstacles){
        std::vector<float> obstacles_pose; 
        int count = 0;
        for(auto const& rect : obstacles){
                obstacles_pose.push_back(rect.min[0]);
                obstacles_pose.push_back(rect.min[1]);
                obstacles_pose.push_back(rect.min[2]);
                obstacles_pose.push_back(rect.max[0]);
                obstacles_pose.push_back(rect.max[1]);
                obstacles_pose.push_back(rect.max[2]);
                count += 1;
        }
        cnpy::npy_save("/dataset/obstacles.npy",&obstacles_pose[0],{1, count, 6},"w");
    }

    void RRTStar3D::save_poses(Eigen::VectorXd start, Eigen::VectorXd end){
       std::vector<float> obstacles_pose(6); 
       obstacles_pose[0] = start[0];
       obstacles_pose[1] = start[1];
       obstacles_pose[2] = start[2];
       obstacles_pose[3] = end[0];
       obstacles_pose[4] = end[1];
       obstacles_pose[5] = end[2];
       cnpy::npy_save("/dataset/start_and_end_pose.npy",&obstacles_pose[0],{obstacles_pose.size()},"w");
    }

    void RRTStar3D::save_path(std::vector<Eigen::VectorXd> path){
       std::vector<float> projected_path; 
        
       std::cout<< "RRTStar3D::save_path trajectory size: " << path.size()<< std::endl;

       for(auto const& way_point : path){
           projected_path.push_back(way_point[0]);
           projected_path.push_back(way_point[1]);
           projected_path.push_back(way_point[2]);
       }
       cnpy::npy_save("/dataset/rrt_star_path.npy",&projected_path[0],{path.size(), 3},"w");
    }
}
}