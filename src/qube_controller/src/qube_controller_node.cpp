
#include "../include/qube_controller/qube_controller_node.hpp"

#include "rclcpp/rclcpp.hpp"
#include "qube_controller/qube_controller_node.hpp"


using namespace std::chrono_literals;




qube_controller::qube_controller(
    const std::string & node_name,
    const std::string & sub_topic,
    const std::string & pub_topic,
    const std::string & sub_topic2,
    std::chrono::milliseconds period)
: Node(node_name)
{
    initSubscribers(sub_topic,sub_topic2);
    initPublisher(pub_topic);
    initTimers(period);


}




void qube_controller::sub(const sensor_msgs::msg::JointState::SharedPtr msg)
{
    pid.setCon(msg->velocity[0]);


}

void qube_controller::sub2(const std_msgs::msg::Float64::SharedPtr data)
{
    pid.setRef(data->data);


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
    const std::string& ref,const std::string& reference)
{
    sub_ = create_subscription<sensor_msgs::msg::JointState>(
        ref, 10,
        std::bind(&qube_controller::sub, this, std::placeholders::_1));
    sub2_ = create_subscription<std_msgs::msg::Float64>(
        reference, 10,
        std::bind(&qube_controller::sub2, this, std::placeholders::_1));
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
      "/reference",         //sub
      std::chrono::milliseconds(20));


    rclcpp::executors::MultiThreadedExecutor executor;
    executor.add_node(qube_controller_node);
    executor.spin();

    rclcpp::shutdown();
    return 0;
}