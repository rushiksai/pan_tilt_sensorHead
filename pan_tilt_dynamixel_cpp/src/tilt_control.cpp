#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"

#include "dynamixel_interface.hpp"

class TiltControl : public rclcpp::Node
{
public:

    TiltControl()
    : Node("tilt_control")
    {
        //-----------------------------------------
        // Connect to Dynamixel
        //-----------------------------------------

        if (!dxl_.connect("/dev/ttyUSB0", 57600))
        {
            RCLCPP_ERROR(
                this->get_logger(),
                "Failed to connect to Dynamixel!"
            );
        }
        else
        {
            RCLCPP_INFO(
                this->get_logger(),
                "Connected to Dynamixel."
            );

            // Slow movement for testing
            dxl_.setProfileVelocity(1, 5);
        }

        //-----------------------------------------
        // Subscriber
        //-----------------------------------------

        subscription_ =
            this->create_subscription<std_msgs::msg::Float64>(
                "/tilt_goal",
                10,
                std::bind(
                    &TiltControl::callback,
                    this,
                    std::placeholders::_1
                )
            );

        RCLCPP_INFO(
            this->get_logger(),
            "Tilt Control Started"
        );
    }

    ~TiltControl()
    {
        dxl_.disconnect();
    }

private:

    void callback(
        const std_msgs::msg::Float64::SharedPtr msg
    )
    {
        RCLCPP_INFO(
            this->get_logger(),
            "Tilt Goal Received: %.3f rad",
            msg->data
        );

        if (!dxl_.sendPositionCommand(
                1,      // Tilt Motor ID
                msg->data))
        {
            RCLCPP_ERROR(
                this->get_logger(),
                "Failed to move Tilt motor!"
            );
        }
    }

    DynamixelInterface dxl_;

    rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);

    auto node =
        std::make_shared<TiltControl>();

    rclcpp::spin(node);

    rclcpp::shutdown();

    return 0;
}