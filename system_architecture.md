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

	[command:1][dir:1][distance:14][sign:1][angle:7]

| Bit(s)       | Field     | Description                                |
|--------------|-----------|--------------------------------------------|
| 1            | Command   | 1-bit command flag (e.g., go/stop)         |
| 1            | Dir       | Direction bit (0 = forward, 1 = backward)  |
| 14           | Distance  | Distance from ToF sensor (0–16383)         |
| 1            | Sign      | Sign of angle (0 = +, 1 = -)               |
| 7            | Angle     | Angle magnitude (0–127)                    |

> Total: **1 + 1 + 14 + 1 + 7 = 24 bits**

---

### 📦 Example Packet Content

- `Command: 1` → Go  
- `Dir: 0` → Forward  
- `Distance: 8020`  
- `Sign: 1` → Negative angle  
- `Angle: 35`

Binary structure of payload (24-bit example):
```
[1][0][00011111010100][1][0100011]
```

---

## 🔄 Full Data Flow Summary

1. **ESP32 reads ToF sensor** ➝ constructs 3-byte packed message using:
   - Command bit
   - Dir bit
   - Distance (14 bits)
   - Sign and Angle
2. **ESP32 builds 6-byte UART packet**:
   - `0xAA` (Start byte)
   - 3 bytes of payload
   - 1-byte checksum (XOR of payload)
   - `0x55` (End byte)
3. **ESP32 sends UART packet** to STM32.
4. **STM32 verifies**:
   - Start and end framing
   - Payload checksum
5. **STM32 responds with ACK** (`0xCC`) if valid.
6. **STM32 decodes and executes** the control command.
