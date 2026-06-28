#include "dynamixel_interface.hpp"

#include <iostream>

int main()
{
    DynamixelInterface dxl;

    std::cout << "Connecting..." << std::endl;

    if (!dxl.connect("/dev/ttyUSB0", 57600))
    {
        std::cout << "Connection Failed!" << std::endl;
        return 0;
    }

    std::cout << "Connection Successful!" << std::endl;

    // VERY SLOW SPEED
    dxl.setProfileVelocity(1, 1);

    // Small movement (~0.57 degrees)
    dxl.sendPositionCommand(1, 0.09);

    std::cout << "Motor moved successfully!" << std::endl;

    dxl.disconnect();

    return 0;
}