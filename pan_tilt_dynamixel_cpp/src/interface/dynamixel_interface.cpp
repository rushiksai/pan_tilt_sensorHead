#include "dynamixel_interface.hpp"

#include <iostream>
#include <cmath>

#define PROTOCOL_VERSION 2.0



#define ADDR_OPERATING_MODE      11
#define ADDR_TORQUE_ENABLE       64
#define ADDR_PROFILE_VELOCITY   112
#define ADDR_GOAL_POSITION      116
#define ADDR_PRESENT_POSITION   132

#define TORQUE_ENABLE 1

#define DXL_MIN_POSITION 0
#define DXL_MAX_POSITION 4095

DynamixelInterface::DynamixelInterface()
{
    connected_ = false;
    portHandler_ = nullptr;
    packetHandler_ = nullptr;
}

bool DynamixelInterface::connect(
    const std::string &device_name,
    int baudrate,
    int dxl_id)
{
    portHandler_ =
        dynamixel::PortHandler::getPortHandler(
            device_name.c_str());

    packetHandler_ =
        dynamixel::PacketHandler::getPacketHandler(
            PROTOCOL_VERSION);

    if (!portHandler_->openPort())
    {
        std::cout << "Failed to open port" << std::endl;
        return false;
    }

    std::cout << "Port opened" << std::endl;

    if (!portHandler_->setBaudRate(baudrate))
    {
        std::cout << "Failed to set baudrate" << std::endl;
        return false;
    }

    std::cout << "Baudrate set" << std::endl;

    uint8_t dxl_error = 0;
    uint16_t model_number = 0;

    int dxl_comm_result =
        packetHandler_->ping(
        portHandler_,
        dxl_id,
        &model_number,
        &dxl_error);
    if (dxl_comm_result != COMM_SUCCESS)
    {
        std::cout
            << "PING FAILED: "
            << packetHandler_->getTxRxResult(dxl_comm_result)
            << std::endl;

        return false;
    }

    std::cout << "PING SUCCESS" << std::endl;
    std::cout << "Model Number = " << model_number << std::endl;

    uint8_t operating_mode = 0;

    packetHandler_->read1ByteTxRx(
        portHandler_,
        dxl_id,
        ADDR_OPERATING_MODE,
        &operating_mode,
        &dxl_error);

    std::cout
        << "Operating Mode = "
        << (int)operating_mode
        << std::endl;

    packetHandler_->write1ByteTxRx(
        portHandler_,
        dxl_id,
        ADDR_TORQUE_ENABLE,
        TORQUE_ENABLE,
        &dxl_error);

    std::cout << "Torque Enabled" << std::endl;

    connected_ = true;

    std::cout << "Connection Successful" << std::endl;

    return true;
}

void DynamixelInterface::disconnect()
{
    if (portHandler_ != nullptr)
        portHandler_->closePort();

    connected_ = false;
}

bool DynamixelInterface::setProfileVelocity(
    int dxl_id,
    uint32_t velocity)
{
    uint8_t dxl_error = 0;

    int dxl_comm_result =
        packetHandler_->write4ByteTxRx(
            portHandler_,
            dxl_id,
            ADDR_PROFILE_VELOCITY,
            velocity,
            &dxl_error);

    if (dxl_comm_result != COMM_SUCCESS)
    {
        std::cout
            << packetHandler_->getTxRxResult(
                   dxl_comm_result)
            << std::endl;

        return false;
    }

    std::cout
        << "Profile Velocity = "
        << velocity
        << std::endl;

    return true;
}

double DynamixelInterface::getCurrentPosition(
    int dxl_id)
{
    uint8_t dxl_error = 0;

    uint32_t present_position = 0;

    int dxl_comm_result =
        packetHandler_->read4ByteTxRx(
            portHandler_,
            dxl_id,
            ADDR_PRESENT_POSITION,
            &present_position,
            &dxl_error);

    if (dxl_comm_result != COMM_SUCCESS)
    {
        std::cout
            << packetHandler_->getTxRxResult(
                   dxl_comm_result)
            << std::endl;

        return 0.0;
    }

    std::cout
        << "Present Position = "
        << present_position
        << std::endl;

    return static_cast<double>(present_position);
}

bool DynamixelInterface::moveRelativeCounts(
    int dxl_id,
    int offset_counts)
{
    uint8_t dxl_error = 0;

    uint32_t present_position = 0;

    int dxl_comm_result =
        packetHandler_->read4ByteTxRx(
            portHandler_,
            dxl_id,
            ADDR_PRESENT_POSITION,
            &present_position,
            &dxl_error);

    if (dxl_comm_result != COMM_SUCCESS)
    {
        std::cout
            << packetHandler_->getTxRxResult(
                   dxl_comm_result)
            << std::endl;

        return false;
    }

    int goal_position =
        static_cast<int>(present_position)
        + offset_counts;

    if (goal_position < DXL_MIN_POSITION)
        goal_position = DXL_MIN_POSITION;

    if (goal_position > DXL_MAX_POSITION)
        goal_position = DXL_MAX_POSITION;

    dxl_comm_result =
        packetHandler_->write4ByteTxRx(
            portHandler_,
            dxl_id,
            ADDR_GOAL_POSITION,
            goal_position,
            &dxl_error);

    if (dxl_comm_result != COMM_SUCCESS)
    {
        std::cout
            << packetHandler_->getTxRxResult(
                   dxl_comm_result)
            << std::endl;

        return false;
    }

    std::cout
        << "Current Encoder = "
        << present_position
        << std::endl;

    std::cout
        << "Goal Encoder = "
        << goal_position
        << std::endl;

    return true;
}

bool DynamixelInterface::sendPositionCommand(
    int dxl_id,
    double position_rad)
{
    double revolutions =
        position_rad / (2.0 * M_PI);

    int goal_position =
        static_cast<int>(
            revolutions * 4095.0);

    goal_position += 2048;

    if (goal_position < DXL_MIN_POSITION)
        goal_position = DXL_MIN_POSITION;

    if (goal_position > DXL_MAX_POSITION)
        goal_position = DXL_MAX_POSITION;

    uint8_t dxl_error = 0;

    int dxl_comm_result =
        packetHandler_->write4ByteTxRx(
            portHandler_,
            dxl_id,
            ADDR_GOAL_POSITION,
            goal_position,
            &dxl_error);

    if (dxl_comm_result != COMM_SUCCESS)
    {
        std::cout
            << packetHandler_->getTxRxResult(
                   dxl_comm_result)
            << std::endl;

        return false;
    }

    std::cout
        << "Goal Position Sent = "
        << goal_position
        << std::endl;

    return true;
}