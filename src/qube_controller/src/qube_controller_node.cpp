
#include "../include/qube_controller/qube_controller_node.hpp"

#include "rclcpp/rclcpp.hpp"
#include "qube_controller/qube_controller_node.hpp"


using namespace std::chrono_literals;




qube_controller::qube_controller(
    const std::string & node_name,
    const std::string & sub_topic,
    const std::string & pub_topic,
    std::chrono::milliseconds period)
: Node(node_name)
{
    initSubscribers(sub_topic);
    initPublisher(pub_topic);
    initTimers(period);


}




void qube_controller::sub(const sensor_msgs::msg::JointState::SharedPtr msg)
{
    pid.setCon(msg->velocity[0]);

}




void qube_controller::pub()
{
  pid.update();
  std_msgs::msg::Float64MultiArray msg;
  msg.data = {pid.getOutput()};
  pub_->publish(msg);
}



//constructor helper methods below
void qube_controller::initSubscribers(
    const std::string& ref)
{
    sub_ = create_subscription<sensor_msgs::msg::JointState>(
        ref, 10,
        std::bind(&qube_controller::sub, this, std::placeholders::_1));
}



void qube_controller::initPublisher(const std::string& topic)
{
    pub_ = create_publisher<std_msgs::msg::Float64MultiArray>(topic, 10);
}


void qube_controller::initTimers(std::chrono::milliseconds period)
{
    timer_ = create_wall_timer(
        period,
        std::bind(&qube_controller::pub, this));
}










int main(int argc, char **argv) {


    rclcpp::init(argc, argv);


    auto qube_controller_node = std::make_shared<qube_controller>(
      "qube_controller",
      "/joint_states",         //sub
      "/velocity_controller/commands",       // pub
      std::chrono::milliseconds(20));


    rclcpp::executors::MultiThreadedExecutor executor;
    executor.add_node(qube_controller_node);
    executor.spin();

    rclcpp::shutdown();
    return 0;
}