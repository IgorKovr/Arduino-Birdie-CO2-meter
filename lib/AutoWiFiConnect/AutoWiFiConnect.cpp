#include "AutoWiFiConnect.h"

AutoWiFiConnect::AutoWiFiConnect()
{
  maxNetworks = 10; // Maximum number of networks to store
  networkCount = 0;
  networks = new Network[maxNetworks];
}

void AutoWiFiConnect::addNetwork(const char *ssid, const char *password)
{
  if (networkCount < maxNetworks)
  {
    networks[networkCount].ssid = ssid;
    networks[networkCount].password = password;
    networkCount++;
  }
}

bool AutoWiFiConnect::connectToAvailableNetwork()
{
  Serial.println("Scanning for WiFi networks...");
  int n = WiFi.scanNetworks();
  if (n == 0)
  {
    Serial.println("No networks found.");
    return false;
  }
  else
  {
    Serial.println("Networks found:");
    for (int i = 0; i < n; ++i)
    {
      String foundSSID = WiFi.SSID(i);
      Serial.println(foundSSID);
      for (int j = 0; j < networkCount; ++j)
      {
        if (foundSSID == networks[j].ssid)
        {
          Serial.print("Attempting to connect to ");
          Serial.println(networks[j].ssid);
          WiFi.begin(networks[j].ssid, networks[j].password);

          unsigned long startTime = millis();
          while (WiFi.status() != WL_CONNECTED && millis() - startTime < 10000)
          {
            delay(500);
            Serial.print(".");
          }

          if (WiFi.status() == WL_CONNECTED)
          {
            Serial.println("\nConnected successfully!");
            return true;
          }
          else
          {
            Serial.println("\nConnection failed.");
          }
        }
      }
    }
  }
  Serial.println("No known networks are available.");
  return false;
}