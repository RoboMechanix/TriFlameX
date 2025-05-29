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
- **Subscribes** to control messages from the Laptop and **forwards them via UART** to its corresponding STM32 using a **custom binary protocol**.

### 📟 STM32 Microcontrollers
- Connected to ESP32s via **UART**.
- **Parses and verifies** the received data with checksum and framing.
- **Sends ACK** (`0xCC`) on successful reception.
- **Executes commands** (e.g., motor/servo actuation).

---

## 🧱 UART Packet Format

Each UART packet sent from ESP32 to STM32 consists of **6 bytes**:

| Byte Index | Field        | Description                                       |
|------------|--------------|---------------------------------------------------|
| 0          | Start Byte   | `0xAA` — indicates beginning of message           |
| 1–3        | Payload      | 3-byte packed data (see layout below)             |
| 4          | Checksum     | XOR of bytes 1–3                                  |
| 5          | End Byte     | `0x55` — indicates end of message                 |

### 🔐 Checksum:
- Ensures data integrity.
- `checksum = byte1 ^ byte2 ^ byte3`

### 📩 ACK:
- STM32 replies with `0xCC` after successful message parsing and checksum validation.

---

## 🧱 Bit Layout (24 bits = 3 bytes Payload):

	[command:1][distance:15][sign:1][angle:7]

| Bit(s)       | Field     | Description                              |
|--------------|-----------|------------------------------------------|
| 1            | Command   | 1-bit command flag (e.g., start/stop)    |
| 15           | Distance  | Distance value from ToF sensor (0–32767) |
| 1            | Sign      | Sign bit for angle (+/-)                 |
| 7            | Angle     | Angle value (0–127)                      |

- **Example:**
  - `Command: 1` → Start
  - `Distance: 3020`
  - `Sign: 0` → Positive
  - `Angle: 45`

---

## 🔄 Full Data Flow Summary

1. **ESP32 reads ToF sensor** ➝ constructs 3-byte packed message.
2. **ESP32 builds 6-byte UART packet** with:
   - Start byte
   - Payload
   - Checksum
   - End byte
3. **ESP32 sends packet via UART** to STM32.
4. **STM32 receives packet**:
   - Verifies start byte
   - Extracts payload
   - Validates checksum
   - Verifies end byte
5. **STM32 sends ACK** (`0xCC`) to ESP32 if all checks pass.
6. **ESP32 optionally checks for ACK** and logs success/failure.
7. **STM32 decodes payload** ➝ executes command (e.g., start/stop motor).

---
