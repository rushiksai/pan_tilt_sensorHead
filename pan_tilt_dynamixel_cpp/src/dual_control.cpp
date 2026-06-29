#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"

#include "interface/dynamixel_interface.hpp"

class DualControl : public rclcpp::Node
{
public:

    DualControl()
    : Node("dual_control")
    {
        //-----------------------------------------
        // Connect to Dynamixel
        //-----------------------------------------

        if (!dxl_.connect("/dev/ttyUSB1", 57600,1))
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

            // Slow profile velocity for testing
            dxl_.setProfileVelocity(1, 5);   // Tilt
            dxl_.setProfileVelocity(2, 5);   // Pan
        }

        //-----------------------------------------
        // Pan Subscriber
        //-----------------------------------------

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

        //-----------------------------------------
        // Tilt Subscriber
        //-----------------------------------------

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

    ~DualControl()
    {
        dxl_.disconnect();
    }

private:

    //-----------------------------------------
    // Pan Callback
    //-----------------------------------------

    void pan_callback(
        const std_msgs::msg::Float64::SharedPtr msg
    )
    {
        RCLCPP_INFO(
            this->get_logger(),
            "Pan Goal Received: %.3f rad",
            msg->data
        );

        if (!dxl_.sendPositionCommand(
                2,
                msg->data))
        {
            RCLCPP_ERROR(
                this->get_logger(),
                "Failed to move Pan motor!"
            );
        }
    }

    //-----------------------------------------
    // Tilt Callback
    //-----------------------------------------

    void tilt_callback(
        const std_msgs::msg::Float64::SharedPtr msg
    )
    {
        RCLCPP_INFO(
            this->get_logger(),
            "Tilt Goal Received: %.3f rad",
            msg->data
        );

        if (!dxl_.sendPositionCommand(
                1,
                msg->data))
        {
            RCLCPP_ERROR(
                this->get_logger(),
                "Failed to move Tilt motor!"
            );
        }
    }

    DynamixelInterface dxl_;

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