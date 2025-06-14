
# TriFlameX

**TriFlameX** is an STM32-based firmware project designed to enable seamless control of multiple cars (blue, red, black) in both autonomous and manual modes. The system leverages MQTT and ROS2 for communication, allowing real-time control, monitoring, and coordination of vehicles.

---

## Features

- Supports autonomous and manual driving modes
- MQTT-based communication for control commands and status updates
- Real-time coordination between multiple cars
- Integration with ROS2 for modular and scalable software architecture
- Robust connectivity monitoring and message handling
- Control message format with commands, direction, distance, and angle
- Smooth switching between manual and autonomous operation

---

## Hardware

- ESP32 microcontroller
- Motor drivers and PWM control for vehicle actuation
- Sensors (e.g., IMU, encoders) for feedback (optional, based on your implementation)
- Wireless communication module (Wi-Fi for MQTT)

---

## Software Architecture

- Firmware runs on ESP32 with FreeRTOS for task management
- ROS2 nodes handle communication and control logic
- MQTT broker for message exchange
- Python or C++ clients for higher-level control and monitoring
- Topics:
  - /car/control for sending driving commands
  - /car/status for reporting car state and connectivity

---

## Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/RoboMechanix/TriFlameX/
   cd TriFlameX
   ```

2. Install dependencies:

   - ESP-IDF for ESP32 firmware development
   - ROS2 Humble (or the ROS2 version you use)
   - MQTT Broker (e.g., Mosquitto)

3. Flash the firmware to the ESP32:

   ```bash
   idf.py -p /dev/ttyUSB0 flash monitor
   ```

4. Run the MQTT broker and ROS2 nodes on your host PC.

---

## Usage

- **Manual Mode:** Control cars directly via MQTT messages or ROS2 topics.
- **Autonomous Mode:** Cars operate based on autonomous navigation algorithms implemented in ROS2.
- Switch modes dynamically by sending control commands.

---

## Communication Protocol

Control messages are packed and include:

| Field      | Description                    |
|------------|-------------------------------|
| Command    | Type of control command       1 bit   |
| Direction  | Direction of movement         1 bit   |
| Distance   | Distance to move or target    14 bit  |
| Angle      | Steering angle or turn value  8 bit   |

---

## Project Structure

See 

## Contribution

Contributions are welcome! Please open an issue or submit a pull request with improvements or bug fixes.

---

## License

Specify your license here (e.g., MIT, GPLv3)

---

## Contact

For questions or support, contact Mohammed Abdelazim at [your email] or via GitHub [YourGitHubUsername].
