#include "astar_improved.h"

namespace kamaz {
namespace hagen {

bool AStarImproved::init_planner(){
	return false;
	}

int AStarImproved::to1D( int x, int y, int z) {
    return (z * w * h) + (y * w) + x;
}

std::array<int, 3> AStarImproved::to3D(int idx) {
    std::array<int, 3> converted;
    int z = idx / (w * h);
    idx -= (z * w * h);
    int y = idx / w;
    int x = idx % w;
    converted[0] = x;
    converted[1] = y;
    converted[2] = z;
    return converted;
}

bool AStarImproved::isValid(int x, int y, int z) { 
	if (x < 0 || y < 0 || z < 0 || x >= w || y >= h || z >= d) {
		return false;
	}else{
		Eigen::Vector3d search_rect(3);
		search_rect << x, y, z;
		if(search_space.obstacle_free(search_rect)){
			return true;
		}
		std::cout<< "Point is too close to obstacle->>>>>>>>"<<  std::endl;
		return false;
	}
}

std::vector<int> AStarImproved::getNeighbors(int idx, bool diagonal) {
		
		std::vector<int> neighbors;
		auto current = to3D(idx);
		int x = current[0];
		int y = current[1];
		int z = current[2];

		// down
		if(isValid(x-1, y, z)) {
			neighbors.push_back(to1D(x-1, y, z));
		}else{
			neighbors.push_back(-1);
		}

		//up
		if(isValid(x+1, y, z)) {
			neighbors.push_back(to1D(x+1, y, z));
		}else{
			neighbors.push_back(-1);
		}

		//left
		if(isValid(x, y-1, z)) {
			neighbors.push_back(to1D(x, y-1, z));
		}else{
			neighbors.push_back(-1);
		}

		//right
		if(isValid(x, y+1, z)) {
			neighbors.push_back(to1D(x, y+1, z));
		}else{
      		neighbors.push_back(-1);
    	}

		//bottom down
		if(isValid(x-1, y, z-1)) {
			neighbors.push_back(to1D(x-1, y, z-1));
		}else{
      		neighbors.push_back(-1);
    	}

		//bottom up
		if(isValid(x+1, y, z-1)) {
			neighbors.push_back(to1D(x+1, y, z-1));
		}else{
      		neighbors.push_back(-1);
    	}

		//bottom left
		if(isValid(x, y-1, z-1)) {
			neighbors.push_back(to1D(x, y-1, z-1));
		}else{
      		neighbors.push_back(-1);
    	}

		//bottom right
		if(isValid(x, y+1, z-1)) {
			neighbors.push_back(to1D(x, y+1, z-1));
		}else{
      		neighbors.push_back(-1);
    	}

		//top down
		if(isValid(x-1, y, z+1)) {
			neighbors.push_back(to1D(x-1, y, z+1));
		}else{
      		neighbors.push_back(-1);
    	}

		//top up
		if(isValid(x+1, y, z+1)) {
			neighbors.push_back(to1D(x+1, y, z+1));
		}else{
      		neighbors.push_back(-1);
    	}

		//top left
		if(isValid(x, y-1, z+1)) {
			neighbors.push_back(to1D(x, y-1, z+1));
		}else{
      		neighbors.push_back(-1);
    	}

		//top right
		if(isValid(x, y+1, z+1)) {
			neighbors.push_back(to1D(x, y+1, z+1));
		}else{
      		neighbors.push_back(-1);
    	}

		//8-Way
		if (diagonal) {
			//left down
			if(isValid(x-1, y-1, z)) {
					neighbors.push_back(to1D(x-1, y-1, z));
			}
			
			//left up
			if(isValid(x+1, y-1, z)) {
				neighbors.push_back(to1D(x+1, y-1, z));
			}

			//right down
			if(isValid(x-1, y+1, z)) {
				neighbors.push_back(to1D(x-1, y+1, z));
			}

			//right up
			if(isValid(x+1, y+1, z)) {
				neighbors.push_back(to1D(x+1, y+1, z));
			}

			//bottom left down
			if(isValid(x-1, y-1, z-1)) {
					neighbors.push_back(to1D(x-1, y-1, z-1));
			}
			
			//bottom left up
			if(isValid(x+1, y-1, z-1)) {
				neighbors.push_back(to1D(x+1, y-1, z-1));
			}

			//bottom right down
			if(isValid(x-1, y+1, z-1)) {
				neighbors.push_back(to1D(x-1, y+1, z-1));
			}

			//bottom right up
			if(isValid(x+1, y+1, z-1)) {
				neighbors.push_back(to1D(x+1, y+1, z-1));
			}

			//top left down
			if(isValid(x-1, y-1, z+1)) {
				neighbors.push_back(to1D(x-1, y-1, z+1));
			}
			
			//top left up
			if(isValid(x+1, y-1, z+1)) {
				neighbors.push_back(to1D(x+1, y-1, z+1));
			}

			//top right down
			if(isValid(x-1, y+1, z+1)) {
				neighbors.push_back(to1D(x-1, y+1, z+1));
			}

			//top right up
			if(isValid(x+1, y+1, z+1)) {
				neighbors.push_back(to1D(x+1, y+1, z+1));
			}
		}
		return neighbors;
}


std::vector<Eigen::Vector3d> AStarImproved::astar_planner_and_save(SearchSpace X,  Eigen::Vector3d x_init, 
									Eigen::Vector3d x_goal){
						auto path = astar_planner(X, x_init, x_goal);
						save_path(path);
						return path;				
}

double  AStarImproved::get_distance(std::vector<Eigen::Vector3d> trajectory_){
			double distance = 0.0f;
      if(trajectory_.size() < 1){
        return distance;
      }
      Eigen::Vector3d previous = trajectory_[0].head(3);
      for (int i = 1; (unsigned)i < trajectory_.size(); i++){
           double dis = std::abs((previous.head(3) - trajectory_[i].head(3)).norm());
           previous = trajectory_[i].head(3);
           distance += dis;
      }
      return distance;
}

  double AStarImproved::get_cost_of_path(std::vector<Eigen::Vector3d> path1){
    int size_of_path = path1.size();
    Eigen::Vector3d path1_dis(size_of_path);
    for(int i=0; i< path1.size(); i++){
        path1_dis[i] = path1[i].head(3).norm();
    }
    Eigen::MatrixXd smoothed_map  = Eigen::MatrixXd::Zero(size_of_path, size_of_path);
    for(int i=0; i<size_of_path-1; i++){
      smoothed_map(i,i) = 2;
      smoothed_map(i,i+1) = smoothed_map(i+1,i) = -1;
    }
    smoothed_map(size_of_path-1, size_of_path-1) = 2;
    return path1_dis.transpose()*smoothed_map*path1_dis;
  }

std::vector<Eigen::Vector3d> AStarImproved::astar_planner(SearchSpace X,  Eigen::Vector3d x_init, 
									Eigen::Vector3d x_goal){

		float_max = 200000000.45;
		search_space = X;

		w = search_space.dim_lengths[1];
		h = search_space.dim_lengths[3];
		d = search_space.dim_lengths[5];
		
		start_idx = to1D(x_init[0], x_init[1], x_init[2]);
		goal_idx = to1D(x_goal[0], x_goal[1], x_goal[2]);
		std::cout<< "rows: " << w << " cols:" << h << " depth: " << d << std::endl;

		std::vector<int> paths(w*h*d);

		std::ofstream outfile;
    outfile.open("/dataset/rrt_old/time_stamps.txt", std::ios_base::app);
    const clock_t begin_time = clock();
    bool success = astar(start_idx, goal_idx, false, paths);
    double time_diff =  double( clock () - begin_time ) /  CLOCKS_PER_SEC;
	
       
		std::vector<Eigen::Vector3d> projected_trajectory;
		if(success){
				std::cout<< "Path is found"<< std::endl;
				auto path_idx = goal_idx;
				int path_node_id=0;
				while(path_idx != start_idx){
						auto path_position = to3D(path_idx);
						Eigen::Vector3d poseh(3);
						poseh << path_position[0], path_position[1], path_position[2];
						projected_trajectory.push_back(poseh);
						path_idx = paths[path_idx];
						path_node_id++;
				}
				auto start_position = to3D(path_idx);
				Eigen::Vector3d poseh(3);
				poseh << start_position[0], start_position[1], start_position[2];
				projected_trajectory.push_back(poseh);
		}else{
				std::cout<< "Path is not found"<< std::endl;
		}
		double dis = get_distance(projected_trajectory);
		outfile << "astar,"<<  time_diff <<","<< projected_trajectory.size() << "," << dis << "," << get_cost_of_path(projected_trajectory)<< "\n";
    
		return projected_trajectory;
}


// weights:        flattened h x w grid of costs
// h, w:           height and width of grid
// start, goal:    index of start/goal in flattened grid
// diag_ok:        if true, allows diagonal moves (8-conn.)
// paths (output): for each node, stores previous node in path
bool AStarImproved::astar(const int start, const int goal, bool diag_ok, std::vector<int>& paths) {

  const double INF = std::numeric_limits<double>::infinity();
  AStarImproved::Node start_node(start, 0.);
  AStarImproved::Node goal_node(goal, 0.);

//   double* costs = new double[h * w * d];
  std::vector<double> costs(h*w*d);
  for (int i = 0; i < h * w * d; ++i)
    costs[i] = INF;
  costs[start] = 0.;
   
  std::priority_queue<AStarImproved::Node> nodes_to_visit;
  nodes_to_visit.push(start_node);
  bool solution_found = false;
  while (!nodes_to_visit.empty()) {
    AStarImproved::Node cur = nodes_to_visit.top();
    if (cur.idx == goal_node.idx) {
      solution_found = true;
      break;
    }
    nodes_to_visit.pop();
    auto nbrs = getNeighbors(cur.idx, false);
    double heuristic_cost;
    for (int i = 0; i < nbrs.size(); ++i) {
      if (nbrs[i] >= 0) {
        // the sum of the cost so far and the cost of this move
		auto tryy = to3D( nbrs[i]);
		double new_cost = costs[cur.idx] + 0.0;
		if (new_cost < costs[nbrs[i]]) {
          auto current_point = to3D( nbrs[i]);
          auto goal_point = to3D(goal);
          if (diag_ok) {
            heuristic_cost = linf_norm(current_point[0], current_point[1],
                                       goal_point[0],  goal_point[1], current_point[2],  goal_point[2]);
          }
          else {
            heuristic_cost = l1_norm(current_point[0], current_point[1],
                                       goal_point[0],  goal_point[1], current_point[2],  goal_point[2]);
          }
          double priority = new_cost + heuristic_cost;
          nodes_to_visit.push(AStarImproved::Node(nbrs[i], priority));
          costs[nbrs[i]] = new_cost;
          paths[nbrs[i]] = cur.idx;
        }
      }
    }
  }
  
  return solution_found;
}

	   void AStarImproved::save_path(std::vector<Eigen::Vector3d> path){
       std::vector<double> projected_path; 
       std::cout<< "Astar::save_path trajectory size: " << path.size()<< std::endl;
       for(auto const& way_point : path){
           projected_path.push_back(way_point[0]);
           projected_path.push_back(way_point[1]);
           projected_path.push_back(way_point[2]);
       }
       cnpy::npy_save("/dataset/rrt_old/a_star_path.npy",&projected_path[0],{path.size(), 3},"w");
    }
}
}