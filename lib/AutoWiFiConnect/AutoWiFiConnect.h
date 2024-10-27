#ifndef AutoWiFiConnect_h
#define AutoWiFiConnect_h

#include <Arduino.h>
#include <WiFiS3.h> // Include the WiFiS3 library for Uno R4 WiFi

class AutoWiFiConnect {
  public:
    AutoWiFiConnect();
    void addNetwork(const char* ssid, const char* password);
    bool connectToAvailableNetwork();

  private:
    struct Network {
      const char* ssid;
      const char* password;
    };
    Network* networks;
    int networkCount;
    int maxNetworks;
};

#endif