
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




void qube_controller::sub(const std_msgs::msg::Float64::SharedPtr angle)
{
    pid.setCon(angle->data);
}




void qube_controller::pub()
{
  pid.update();
  std_msgs::msg::Float64 voltage;
  voltage.data = pid.getOutput();
  pubVoltage_->publish(voltage);
}



//constructor helper methods below
void qube_controller::initSubscribers(
    const std::string& angle_ref)
{
    subAngle_ = create_subscription<std_msgs::msg::Float64>(
        angle_ref, 10,
        std::bind(&qube_controller::sub, this, std::placeholders::_1));
}



void pid_controller_node::initPublisher(const std::string& topic)
{
    pubVoltage_ = create_publisher<std_msgs::msg::Float64>(topic, 10);
}


void pid_controller_node::initTimers(std::chrono::milliseconds period)
{
    timer_ = create_wall_timer(
        period,
        std::bind(&pid_controller_node::pubVoltage, this));
}




void pid_controller_node::initServices()
{

    service_ = create_service<pid_controller_msgs::srv::SetReference>(
        "/set_reference",
        std::bind(&pid_controller_node::setReference,
        this,
        std::placeholders::_1,
        std::placeholders::_2));
}





int main(int argc, char **argv) {


    rclcpp::init(argc, argv);


    auto qube_controller = std::make_shared<qube_controller_node>(
      "qube_controller",
      "/joint_state",         //sub
      "/velocity_controller/commands",       // pub
      std::chrono::milliseconds(6));


    rclcpp::executors::MultiThreadedExecutor executor;
    executor.add_node(qube_controller);
    executor.spin();

    rclcpp::shutdown();
    return 0;
}