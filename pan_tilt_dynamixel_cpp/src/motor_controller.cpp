#include "rclcpp/rclcpp.hpp"
#include <std_msgs/msg/float64.hpp>

#include "dynamixel_interface.hpp"

class MotorController : public rclcpp::Node
{
public:

    MotorController()
    : Node("motor_controller")
    {
        bool success =
            dxl_interface_.connect(
                "/dev/ttyUSB0",
                57600
            );

        if (success)
        {
            RCLCPP_INFO(
                this->get_logger(),
                "Dynamixel Interface Connected"
            );
        }

        subscription_ =
            this->create_subscription<std_msgs::msg::Float64>(
                "/goal_position",
                rclcpp::QoS(10),
                std::bind(
                    &MotorController::topic_callback,
                    this,
                    std::placeholders::_1
                )
            );

        RCLCPP_INFO(
            this->get_logger(),
            "Motor Controller Node Started"
        );
    }

private:

    void topic_callback(
        const std_msgs::msg::Float64::SharedPtr msg
    )
    {
        double position = msg->data;

        RCLCPP_INFO(
            this->get_logger(),
            "Received Goal Position: %.3f rad",
            position
        );

        dxl_interface_.sendPositionCommand(
            1,
            position
        );
    }

    rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr subscription_;

    DynamixelInterface dxl_interface_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);

    auto node =
        std::make_shared<MotorController>();

    rclcpp::spin(node);

    rclcpp::shutdown();

    return 0;
}


