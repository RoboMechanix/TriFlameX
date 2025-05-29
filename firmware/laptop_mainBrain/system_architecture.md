# 📡 ESP32–STM32 Multi-Node System with Laptop (MQTT over Wi-Fi)

	    	[Laptop]
			   ↑	
  	 	[Wi-Fi / MQTT]
       	       ↑
	[ESP32 #1] — UART — [STM32]
	[ESP32 #2] — UART — [STM32]
	[ESP32 #3] — UART — [STM32]


---

## 🔧 System Overview

### 🖥 Laptop
- Acts as the **central brain**.
- **Receives sensor data** from all ESP32 modules via MQTT over Wi-Fi.
- **Sends control commands** to ESP32 modules (for STM32) based on data analysis or user input.

### 📶 ESP32 Modules (x3)
Each ESP32:
- **Reads Time-of-Flight (ToF) sensor data**.
- **Publishes** this data to the Laptop using **MQTT over Wi-Fi**.
- **Subscribes** to control messages from the Laptop and **forwards them via UART** to its corresponding STM32.

### 📟 STM32 Microcontrollers
- Connected to ESP32s via **UART**.
- **Executes commands** received through ESP32.
- Likely interfaces with actuators or additional sensors.

---

## 🧱 Bit Layout (24 bits = 3 bytes):

	[command:1][distance:15][sign:1][angle:7]

| Bit(s)       | Field     | Description                              |
|--------------|-----------|------------------------------------------|
| 1            | Command   | 1-bit command flag (e.g., start/stop)    |
| 15           | Distance  | Distance value from ToF sensor (0–32767) |
| 1            | Sign      | Sign bit for angle (+/-)                 |
| 7            | Angle     | Angle value (0–127)                      |

- **Example:**
  - `Command: 1` → Start command
  - `Distance: 3020` → ToF sensor measurement
  - `Sign: 0` → Positive angle
  - `Angle: 45` → 45°

---

## 🔄 Data Flow Summary

1. **ESP32 reads ToF sensor** ➝ constructs 3-byte data packet.
2. **ESP32 sends packet to Laptop** over MQTT.
3. **Laptop processes data** ➝ sends new commands via MQTT.
4. **ESP32 receives command** ➝ forwards via UART to STM32.
5. **STM32 executes command** (e.g., move servo/motor).


