# AutoWiFiConnect Library for Arduino Uno R4 WiFi

## Overview

**AutoWiFiConnect** is an Arduino library designed for the Arduino Uno R4 WiFi board. It simplifies the process of connecting your Arduino to WiFi networks by scanning for available networks and automatically connecting to one of your predefined networks if available.

## Features

- **Automatic WiFi Connection**: Scans for available WiFi networks and connects to a known network if found.
- **Multiple Network Support**: Stores multiple WiFi credentials to connect to different networks seamlessly.
- **Easy Integration**: Simple API for adding networks and initiating connections.
- **Debugging Support**: Provides serial output for monitoring connection status and troubleshooting.

## Requirements

- **Hardware**: Arduino Uno R4 WiFi
- **Software**:
  - Arduino IDE (latest version recommended)
  - **WiFiS3** library (included with the board support for Uno R4 WiFi)

## Installation

1. **Download the Library**:

   - Download the `AutoWiFiConnect.h` and `AutoWiFiConnect.cpp` files.

2. **Create Library Folder**:

   - Navigate to your Arduino libraries directory (usually `Documents/Arduino/libraries/`).
   - Create a new folder named `AutoWiFiConnect`.

3. **Add Library Files**:

   - Copy `AutoWiFiConnect.h` and `AutoWiFiConnect.cpp` into the `AutoWiFiConnect` folder.

4. **Restart Arduino IDE**:
   - Close and reopen the Arduino IDE to recognize the new library.

## Usage

### 1. Include the Library

At the top of your Arduino sketch, include the necessary headers:

```cpp
#include <WiFiS3.h>          // WiFi library for Arduino Uno R4 WiFi
#include <AutoWiFiConnect.h> // Include the AutoWiFiConnect library
```

## 2. Create an Instance

Instantiate the AutoWiFiConnect object:

```cpp
AutoWiFiConnect wifiConnector;
```

## 3. Setup Function

In your setup() function, add your known networks and attempt to connect:

```cpp
void setup() {
  Serial.begin(115200);
  delay(1000);

  // Add known networks (SSID and Password)
  wifiConnector.addNetwork("HomeNetwork", "home_password");
  wifiConnector.addNetwork("OfficeNetwork", "office_password");
  wifiConnector.addNetwork("MobileHotspot", "hotspot_password");

  // Attempt to connect to an available network
  if (wifiConnector.connectToAvailableNetwork()) {
    Serial.println("Device connected to WiFi!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Failed to connect to any known WiFi networks.");
  }
}
```

## 4. Loop Function

Your loop() function can remain empty or contain your main code:

```cpp
void loop() {
  // Your main code here
}
```

## 5. Full Example

```cpp
#include <WiFiS3.h>
#include <AutoWiFiConnect.h>

AutoWiFiConnect wifiConnector;

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Add known networks
  wifiConnector.addNetwork("HomeNetwork", "home_password");
  wifiConnector.addNetwork("OfficeNetwork", "office_password");
  wifiConnector.addNetwork("MobileHotspot", "hotspot_password");

  // Attempt to connect
  if (wifiConnector.connectToAvailableNetwork()) {
    Serial.println("Device connected to WiFi!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Failed to connect to any known WiFi networks.");
  }
}

void loop() {
  // Your main code here
}
```

## 6. Example Output

When running the example sketch, you should see output similar to the following in the Serial Monitor:

```log
Scanning for WiFi networks...
Networks found:
HomeNetwork
OfficeNetwork
NeighborNetwork
Attempting to connect to HomeNetwork
......
Connected successfully!
Device connected to WiFi!
IP Address: 192.168.1.100
```

```markdown
## Troubleshooting

- **Compilation Errors**:

  - Ensure that only `WiFiS3.h` is included, and there are no conflicts with other WiFi libraries like `WiFi.h` or `WiFiNINA.h`.
  - Verify that you have selected the correct board (Arduino Uno R4 WiFi) in the Arduino IDE.
  - Make sure you have the latest board definitions and libraries installed.

- **Connection Issues**:
  - Double-check the SSID and password for each network added using `addNetwork()`.
  - Ensure that the networks are within range and operational.
  - Use the Serial Monitor to view debug messages and identify where the connection process may be failing.

## Notes

- **Max Networks**: By default, the library can store up to 10 networks. You can adjust `maxNetworks` in the constructor if you need to store more.
- **Memory Management**: The library dynamically allocates memory for storing network credentials. Ensure your Arduino has sufficient memory if you increase `maxNetworks`.
- **Security**: Be cautious when hardcoding WiFi credentials into your sketches. Avoid sharing your code publicly if it contains sensitive information.

## Limitations

- **WiFi Mode Setting**: The `WiFiS3` library initializes in station mode by default. There's no need to set the WiFi mode explicitly in your code.
- **Compatibility**: This library is specifically designed for the Arduino Uno R4 WiFi using the `WiFiS3` library. It may not work with other boards or WiFi libraries without modification.

## License

This project is licensed under the MIT License.

## Author

[IgorKovr]

Feel free to contribute to this project by submitting issues or pull requests on GitHub.

## Acknowledgments

- Thanks to the Arduino community for continuous support and contributions.
- Inspired by the need for simplified WiFi connectivity in Arduino projects.
```
