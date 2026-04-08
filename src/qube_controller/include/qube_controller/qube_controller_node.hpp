#ifndef BUILD_QUBE_CONTROLLER_NODE_HPP
#define BUILD_QUBE_CONTROLLER_NODE_HPP

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include "std_msgs/msg/float64.hpp"
#include "qube_controller/pid_controller.hpp"
#include <memory>
#include <chrono>


class qube_controller : public rclcpp::Node
{
public:
    qube_controller(
      const std::string & node_name,
      const std::string & sub_topic,
      const std::string & pub_topic,
      const std::string & sub_topic2,
      std::chrono::milliseconds period);
private:

    void sub(const sensor_msgs::msg::JointState::SharedPtr msg);
    void sub2(const std_msgs::msg::Float64::SharedPtr data);

    void pub();





    rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr sub_;

    rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr sub2_;

    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr pub_;

    rclcpp::TimerBase::SharedPtr timer_;


    pidController pid;


    //constructur helper methods
    void initSubscribers(const std::string& sub, const std::string& sub2 );
    void initPublisher(const std::string& pub);
    void initParameters();
    void initTimers(std::chrono::milliseconds period);
    void initServices();


};
#endif //BUILD_QUBE_CONTROLLER_NODE_HPP
