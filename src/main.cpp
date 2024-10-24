#include <Arduino.h>
#include "../include/Secrets.h"
#include "../include/thingProperties.h"
// #include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"
#include "../lib/AutoWiFiConnect.h"
#include "SparkFun_SCD30_Arduino_Library.h"

ArduinoLEDMatrix matrix;
AutoWiFiConnect wifiConnector;
SCD30 airSensor;

// Used for Timer functinoality
unsigned long previousCO2Millis = 0;    // Stores the last time CO2 was read
const unsigned long co2Interval = 2000; // Interval at which to read CO2 in milliseconds

void readAndSendCO2Value();
void onLedChange();
// void playLEDMatrixLoadingAnimation();
void printOnLEDMatrix(String displayText);

void setup()
{
  // playLEDMatrixLoadingAnimation();
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1000);

  // Add known networks (SSID and Password)
  wifiConnector.addNetwork(SECRET_SSID, SECRET_PASS);
  wifiConnector.addNetwork(SECRET_SSID1, SECRET_PASS1);
  wifiConnector.addNetwork(SECRET_SSID2, SECRET_PASS2);

  // Attempt to connect to an available network
  if (wifiConnector.connectToAvailableNetwork())
  {
    Serial.println("Device connected to WiFi!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else
  {
    Serial.println("Failed to connect to any known WiFi networks.");
  }

  // Defined in thingProperties.h
  initProperties();
  // Connect to Arduino IoT Cloud

  // FIXME: If we don't specify the network, begin() doesn't to send any data.
  // However, if we are already conncected to a network, ArduinoIoTPreferredConnection doesn't seem to switch the network.
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  //  Enable Debuggin of the network, IoT Cloud connection, and errors. 4 is MAX
  setDebugMessageLevel(4);
  ArduinoCloud.printDebugInfo();

  // SCD30 Start
  Wire1.begin();
  if (airSensor.begin(Wire1) == false)
  {
    Serial.println("Air sensor not detected. Please check wiring. Freezing...");
    while (1)
      ;
  }

  // Wait for the loading animation to finish
  delay(3300);
  matrix.clear();
  led = true;
  isLedOn = true;
}

void loop()
{
  ArduinoCloud.update();

  // Check if delay have passed since the last CO2 read
  unsigned long currentMillis = millis();
  if (currentMillis - previousCO2Millis >= co2Interval)
  {
    previousCO2Millis = currentMillis; // Update the timestamp for the last CO2 read
    readAndSendCO2Value();
  }
}

void readAndSendCO2Value()
{
  // TODO: Replace with SCD30 Readings
  cO2Level = analogRead(0);

  if (airSensor.dataAvailable())
  {
    cO2Level = airSensor.getCO2();
    Serial.print("co2(ppm):");
    Serial.print(cO2Level);

    Serial.print(" temp(C):");
    Serial.print(airSensor.getTemperature(), 1);

    Serial.print(" humidity(%):");
    Serial.print(airSensor.getHumidity(), 1);

    Serial.println();

    if (led)
    {
      printOnLEDMatrix(String(cO2Level, 0));
      isLedOn = true;
    }
    else
    {
      matrix.clear();
      isLedOn = false;
    }
    delay(2000);
  }
  else
  {
    Serial.println("Waiting for new data");
    delay(1000);
  }
}

// Executed every time a new value is received from IoT Cloud.
// Defined in thingProperties.h
void onLedChange()
{
  Serial.print("Led status changed:");
  Serial.println(led);
}

// void playLEDMatrixLoadingAnimation()
// {
//   matrix.loadSequence(LEDMATRIX_ANIMATION_TETRIS_INTRO);
//   matrix.begin();
//   matrix.play(false); // false == don't repeat animation
// }

void printOnLEDMatrix(String displayText)
{
  matrix.beginDraw();
  matrix.stroke(0xFFFFFFFF);
  matrix.textFont(Font_5x7);
  matrix.beginText(0, 1, 0xFFFFFF);
  matrix.println(displayText);
  matrix.endText(NO_SCROLL);
  matrix.endDraw();
}