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
        int baudrate,
        int dxl_id
    );

    void disconnect();

    bool setProfileVelocity(
        int dxl_id,
        uint32_t velocity
    );

    double getCurrentPosition(
        int dxl_id
    );

    bool sendPositionCommand(
        int dxl_id,
        double position_rad
    );

    bool moveRelativeCounts(
        int dxl_id,
        int offset_counts
    );

private:

    bool connected_;

    dynamixel::PortHandler *portHandler_;
    dynamixel::PacketHandler *packetHandler_;
};

#endif