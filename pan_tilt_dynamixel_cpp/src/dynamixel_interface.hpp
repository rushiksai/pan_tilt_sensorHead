#ifndef DYNAMIXEL_INTERFACE_HPP
#define DYNAMIXEL_INTERFACE_HPP

#include "dynamixel_sdk/dynamixel_sdk.h"
#include <string>

class DynamixelInterface
{
public:

    DynamixelInterface();

    bool connect(
        const std::string &device_name,
        int baudrate
    );

    void disconnect();

    bool setProfileVelocity(
        int dxl_id,
        uint32_t velocity
    );

    bool sendPositionCommand(
        int dxl_id,
        double position_rad
    );

private:

    bool connected_;

    dynamixel::PortHandler *portHandler_;
    dynamixel::PacketHandler *packetHandler_;
};

#endif