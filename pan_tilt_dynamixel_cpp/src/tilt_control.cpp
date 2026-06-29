#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"

#include "interface/dynamixel_interface.hpp"

class TiltControl : public rclcpp::Node
{
public:

    TiltControl()
    : Node("tilt_control")
    {
        //-----------------------------------------
        // Connect to Dynamixel
        //-----------------------------------------

        if (!dxl_.connect("/dev/ttyUSB1", 57600, 1))
        {
            RCLCPP_ERROR(
                this->get_logger(),
                "Failed to connect to Dynamixel!"
            );

            return;
        }

        RCLCPP_INFO(
            this->get_logger(),
            "Connected to Dynamixel."
        );

        dxl_.setProfileVelocity(1, 5);

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
        int offset_counts =
            static_cast<int>(msg->data);

        RCLCPP_INFO(
            this->get_logger(),
            "Tilt Offset = %d counts",
            offset_counts
        );

        if (!dxl_.moveRelativeCounts(
                1,              // Tilt Motor ID
                offset_counts))
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