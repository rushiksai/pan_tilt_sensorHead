#include "interface/dynamixel_interface.hpp"

#include <iostream>

int main()
{
    DynamixelInterface dxl;

    std::cout << "Connecting..." << std::endl;

    if (!dxl.connect("/dev/ttyUSB1", 57600,2))
    {
        std::cout << "Connection Failed!" << std::endl;
        return 0;
    }

    std::cout << "Connection Successful!" << std::endl;

    double position =
    dxl.getCurrentPosition(2);

    std::cout
        << "Current Encoder = "
        << position
        << std::endl;

    // VERY SLOW SPEED
    dxl.setProfileVelocity(2, 1);

    // Small movement (~0.57 degrees)
    // Move forward by 20 encoder counts
    dxl.moveRelativeCounts(2, 1040);

    std::cout << "Motor moved successfully!" << std::endl;

    dxl.disconnect();

    return 0;
}