#include "pid_controller/pid_controller_node.hpp"
#include "rclcpp/rclcpp.hpp"



int main(int argc, char **argv) {


    rclcpp::init(argc, argv);


    auto pidNode = std::make_shared<pid_controller_node>(
      "pid_controller_node",
      "/angle",         //sub
      "/voltage",       // pub
      std::chrono::milliseconds(6));


    rclcpp::executors::MultiThreadedExecutor executor;
    executor.add_node(pidNode);
    executor.spin();

    rclcpp::shutdown();
    return 0;
}