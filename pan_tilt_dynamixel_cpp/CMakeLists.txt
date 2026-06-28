cmake_minimum_required(VERSION 3.8)
project(pan_tilt_dynamixel_cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

include_directories(
  include
  /home/rushiksaiii/Downloads/DynamixelSDK/c++/include
  /home/rushiksaiii/Downloads/DynamixelSDK/c++/include/dynamixel_sdk
)

set(DXL_SDK_SRC
  /home/rushiksaiii/Downloads/DynamixelSDK/c++/src/dynamixel_sdk/group_bulk_read.cpp
  /home/rushiksaiii/Downloads/DynamixelSDK/c++/src/dynamixel_sdk/group_bulk_write.cpp
  /home/rushiksaiii/Downloads/DynamixelSDK/c++/src/dynamixel_sdk/group_fast_bulk_read.cpp
  /home/rushiksaiii/Downloads/DynamixelSDK/c++/src/dynamixel_sdk/group_fast_sync_read.cpp
  /home/rushiksaiii/Downloads/DynamixelSDK/c++/src/dynamixel_sdk/group_handler.cpp
  /home/rushiksaiii/Downloads/DynamixelSDK/c++/src/dynamixel_sdk/group_sync_read.cpp
  /home/rushiksaiii/Downloads/DynamixelSDK/c++/src/dynamixel_sdk/group_sync_write.cpp
  /home/rushiksaiii/Downloads/DynamixelSDK/c++/src/dynamixel_sdk/packet_handler.cpp
  /home/rushiksaiii/Downloads/DynamixelSDK/c++/src/dynamixel_sdk/port_handler.cpp
  /home/rushiksaiii/Downloads/DynamixelSDK/c++/src/dynamixel_sdk/port_handler_linux.cpp
  /home/rushiksaiii/Downloads/DynamixelSDK/c++/src/dynamixel_sdk/protocol1_packet_handler.cpp
  /home/rushiksaiii/Downloads/DynamixelSDK/c++/src/dynamixel_sdk/protocol2_packet_handler.cpp
)

add_executable(
  motor_controller
  src/motor_controller.cpp
  src/dynamixel_interface.cpp
  ${DXL_SDK_SRC}
)

add_executable(
  sdk_ping_test
  src/sdk_ping_test.cpp
  src/dynamixel_interface.cpp
  ${DXL_SDK_SRC}
)

add_executable(
  pan_control
  src/pan_control.cpp
  src/dynamixel_interface.cpp
  ${DXL_SDK_SRC}
)

add_executable(
  tilt_control
  src/tilt_control.cpp
  src/dynamixel_interface.cpp
  ${DXL_SDK_SRC}
)

add_executable(
  dual_control
  src/dual_control.cpp
  src/dynamixel_interface.cpp
  ${DXL_SDK_SRC}
)

ament_target_dependencies(motor_controller rclcpp std_msgs)
ament_target_dependencies(sdk_ping_test rclcpp std_msgs)
ament_target_dependencies(pan_control rclcpp std_msgs)
ament_target_dependencies(tilt_control rclcpp std_msgs)
ament_target_dependencies(dual_control rclcpp std_msgs)

target_link_libraries(motor_controller pthread)
target_link_libraries(sdk_ping_test pthread)
target_link_libraries(pan_control pthread)
target_link_libraries(tilt_control pthread)
target_link_libraries(dual_control pthread)

install(
  TARGETS
    motor_controller
    sdk_ping_test
    pan_control
    tilt_control
    dual_control
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()