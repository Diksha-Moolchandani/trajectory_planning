#ifndef MAV_TRAJECTORY_PLANNING
#define MAV_TRAJECTORY_PLANNING

#include <stack>
#include <vector>
#include <array>
#include <iostream>
#include <cmath>
#include <set>
#include <cstdlib>
#include <climits>
#include <cerrno>
#include <cfenv>
#include <cstring>
#include <cnpy.h>
#include <stack> 
#include <Eigen/Dense>
#include <unsupported/Eigen/NonLinearOptimization>
#include <unsupported/Eigen/NumericalDiff>
#include <Eigen/Eigenvalues> 
#include <complex>
#include <fstream>
#include <random>
#include <cmath>
#include <chrono>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

#include <mav_msgs/conversions.h>
#include <mav_msgs/default_topics.h>
#include <mav_msgs/eigen_mav_msgs.h>
#include <mav_planning_msgs/PolynomialSegment4D.h>
#include <mav_planning_msgs/PolynomialTrajectory4D.h>
#include <ros/ros.h>
#include <std_srvs/Empty.h>
#include <trajectory_msgs/MultiDOFJointTrajectory.h>

#include <mav_trajectory_generation/polynomial.h>
#include <mav_trajectory_generation/trajectory_sampling.h>
#include <mav_trajectory_generation_ros/ros_conversions.h>

#include <mav_trajectory_generation/polynomial_optimization_nonlinear.h>
#include <mav_trajectory_generation/polynomial_optimization_linear.h>
#include <mav_trajectory_generation/trajectory.h>

#include <nav_msgs/Path.h>
#include <iostream>
#include <Eigen/Dense>

namespace kamaz {
namespace hagen {
        class MavTrajectoryPlanning {
            public:
                MavTrajectoryPlanning(double speed = 2);
                ~MavTrajectoryPlanning() = default;

                bool generate_ts(std::vector<Eigen::VectorXd> path);
                void traj_opt7();
                void save_status(std::vector<std::vector<Eigen::VectorXd>>
                        , std::string file_name);
                void save_trajectory(std::vector<Eigen::VectorXd> trajectory_of_drone
                ,  std::string file_name);

                void get_desired_state(double time
                        , std::vector<Eigen::VectorXd>& states);
                std::pair<double, int > closest(double value);

                void generate_target_trajectory(std::vector<Eigen::VectorXd>&  target_trajectory
                       , std::string trajectory_to_be_flown_file_name);

                mav_trajectory_generation::Vertex::Vector vertices;
                double total_time;
                double max_speed;
                Eigen::MatrixXd X;
                Eigen::MatrixXd A;
                Eigen::MatrixXd Y;
                const int dimension = 4;
                std::vector<double> segment_times;
                const double v_max = 2.0;
                const double a_max = 1.0;
                //Linear Optimization
                const int N = 10;
                bool is_set;
                 // The trajectory to sub-sample.
                mav_trajectory_generation::Trajectory trajectory_;
                const int derivative_to_optimize =  mav_trajectory_generation::derivative_order::SNAP;;

            private:
            };
    }
}
#endif