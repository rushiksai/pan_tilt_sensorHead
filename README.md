# Pan-Tilt Dynamixel Control using ROS 2 (C++)

## Overview

This project implements the low-level control of a 2-DOF robotic pan-tilt sensor head using **Dynamixel XM430-W350-R actuators**, **ROS 2 Jazzy**, and the **Dynamixel SDK**.

The project was developed as part of a Master's research project on robotic sensor head development for object perception and future visual servoing applications.

Current implementation focuses on establishing reliable communication between ROS 2 and the Dynamixel actuators through the U2D2 interface.

---

## Features

* ROS 2 C++ implementation
* Individual Pan actuator control
* Individual Tilt actuator control
* Dual actuator control framework
* Dynamixel SDK integration
* Position control using ROS topics
* Configurable profile velocity
* Hardware communication through U2D2 USB interface

---

## Hardware

* Dynamixel XM430-W350-R Servo Motors (2x)
* Dynamixel U2D2 USB Interface
* 12 V Power Supply
* Pan-Tilt Mechanical Assembly
* PC running Ubuntu 24.04 (ROS 2 Jazzy)

---

## Software

* Ubuntu 24.04
* ROS 2 Jazzy
* C++
* CMake
* Dynamixel SDK
* Visual Studio Code

---

## Project Structure

```
pan_tilt_dynamixel_cpp/

├── src/
│   ├── pan_control.cpp
│   ├── tilt_control.cpp
│   ├── dual_control.cpp
│   │
│   ├── interface/
│   │   ├── dynamixel_interface.cpp
│   │   └── dynamixel_interface.hpp
│   │
│   └── test/
│       ├── motor_controller.cpp
│       └── sdk_ping_test.cpp
│
├── CMakeLists.txt
├── package.xml
└── README.md
```

---

## ROS Topics

### Pan Control

Topic:

```
/pan_goal
```

Example:

```bash
ros2 topic pub --once /pan_goal std_msgs/msg/Float64 "{data: 0.25}"
```

---

### Tilt Control

Topic:

```
/tilt_goal
```

Example:

```bash
ros2 topic pub --once /tilt_goal std_msgs/msg/Float64 "{data: -0.20}"
```

---

## Build

```bash
cd ~/pan_tilt_ws

colcon build --packages-select pan_tilt_dynamixel_cpp

source install/setup.bash
```

---

## Run

### Pan Controller

```bash
ros2 run pan_tilt_dynamixel_cpp pan_control
```

### Tilt Controller

```bash
ros2 run pan_tilt_dynamixel_cpp tilt_control
```

### Dual Controller

```bash
ros2 run pan_tilt_dynamixel_cpp dual_control
```

---

## Current Status

✔ Dynamixel SDK communication established

✔ ROS 2 communication established

✔ Individual Pan actuator control

✔ Individual Tilt actuator control

✔ Position commands through ROS topics

✔ Configurable profile velocity

---

## Future Work

* Dual synchronized pan-tilt control
* Encoder feedback
* Forward kinematics
* Inverse kinematics
* Velocity control
* Gaze control
* Camera integration
* Object detection and tracking
* Visual servoing
* Force and torque compensation

---

## Author

**Rushik Sai Jakka**

Master's Student

Control, Microelectronics and Microsystems

University of Bremen

