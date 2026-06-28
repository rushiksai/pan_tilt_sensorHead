#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"

class DualControl : public rclcpp::Node
{
public:

    DualControl()
    : Node("dual_control")
    {
        pan_subscription_ =
            this->create_subscription<std_msgs::msg::Float64>(
                "/pan_goal",
                10,
                std::bind(
                    &DualControl::pan_callback,
                    this,
                    std::placeholders::_1
                )
            );

        tilt_subscription_ =
            this->create_subscription<std_msgs::msg::Float64>(
                "/tilt_goal",
                10,
                std::bind(
                    &DualControl::tilt_callback,
                    this,
                    std::placeholders::_1
                )
            );

        RCLCPP_INFO(
            this->get_logger(),
            "Dual Control Started"
        );
    }

private:

    void pan_callback(
        const std_msgs::msg::Float64::SharedPtr msg
    )
    {
        RCLCPP_INFO(
            this->get_logger(),
            "Pan Goal: %.2f",
            msg->data
        );
    }

    void tilt_callback(
        const std_msgs::msg::Float64::SharedPtr msg
    )
    {
        RCLCPP_INFO(
            this->get_logger(),
            "Tilt Goal: %.2f",
            msg->data
        );
    }

    rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr
        pan_subscription_;

    rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr
        tilt_subscription_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);

    auto node =
        std::make_shared<DualControl>();

    rclcpp::spin(node);

    rclcpp::shutdown();

    return 0;
}