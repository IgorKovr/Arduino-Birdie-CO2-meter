# CO₂ Level Monitor with Arduino Uno R4 WiFi

An Arduino-based CO₂ monitor inspired by Birdie, featuring real-time environmental monitoring and automated controls for a Servo motor. This project is perfect for those interested in DIY air quality monitoring and hardware integration.

## ✨ Project Overview

This project leverages the **Arduino Uno R4 WiFi**, **SCD30 CO₂ sensor**, and **MG90S Servo motor** to measure and respond to CO₂ levels. The project is designed for flexibility, allowing you to connect seamlessly to various WiFi networks using a custom `AutoConnectWiFi` library.

## ⚙️ Key Components

- **Arduino Uno R4 WiFi**: Provides wireless connectivity and serves as the core microcontroller.
- **SCD30 Sensor**: Measures CO₂ concentration in the air, providing real-time environmental data.
- **MG90S Servo Motor**: Responds to CO₂ levels by moving to different positions, demonstrating potential for mechanical actuation based on air quality.

## 📌 Pinout Map

Here’s how to connect each component:

### SCD30 CO₂ Sensor

- **Connection Type**: Qwiic connector

### MG90S Servo Motor

- **Connections**:

  - **GND**: Ground
  - **5V**: Power
  - **Digital Pin 3**: Control signal

### Details:

- **SCD30 Sensor**
  - **Connection Type**: Qwiic connector (only requires a single cable to connect).
- **MG90S Servo Motor**
  - **GND**: Ground
  - **5V**: Power
  - **Digital Pin 3**: Control signal

> Note: You can use a different Servo motor model if needed, but be sure to adjust the wiring and control pin configuration accordingly.

## 🌐 WiFi Configuration with AutoConnectWiFi

This project uses the `AutoConnectWiFi` library for multi-network support. Define WiFi credentials in `include/Secrets.h` (copy from `Secrets_example.h`), enabling seamless operation across different locations.

## 📝 Code Structure: main.cpp

The main functionality resides in `main.cpp`, structured as follows:

1. **Setup**: Initializes the Arduino hardware, establishes a WiFi connection via `AutoConnectWiFi`, and sets up the SCD30 sensor and Servo motor.
2. **Loop**: Continuously reads data from the SCD30 sensor and adjusts the Servo motor’s position based on real-time CO₂ levels.

## 🚀 Getting Started

1. **Install Required Libraries**: Ensure you have the `AutoConnectWiFi` library and any others required for your board and components.
2. **Set up Hardware**: Connect the SCD30 sensor and Servo motor as per the pinout map above.
3. **Configure WiFi**: Update `Secrets.h` with WiFi network details.
4. **Upload the Code**: Upload `CO2_Level.ino` (attached) to your Arduino Uno R4 WiFi board.
5. **Monitor CO₂ Levels**: Once running, the Arduino will log CO₂ levels and actuate the Servo motor when CO₂ exceeds certain thresholds.

## 📂 File Structure

- **`main.cpp`**: Core logic for the project.
- **`include/Secrets.h`**: WiFi credentials.
- **`Secrets_example.h`**: Example WiFi configuration file.

## 💡 Tips

- **Adjust Sensor Reading Intervals**: If you want to monitor at different intervals, modify the sensor reading frequency in the `loop` function.
- **Servo Calibration**: You can customize Servo motor angles based on your needs in the code.
