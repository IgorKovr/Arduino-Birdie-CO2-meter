#include <Arduino.h>
#include "../include/Secrets.h"
#include "../include/thingProperties.h"
#include "Arduino_LED_Matrix.h"
#include <AutoWiFiConnect.h>
#include "SparkFun_SCD30_Arduino_Library.h"
#include <Servo.h>

ArduinoLEDMatrix matrix;
AutoWiFiConnect wifiConnector;
SCD30 airSensor;
Servo servo;

void readAndSendCO2Value();
void onLedChange();
void playLEDMatrixLoadingAnimation();
void printOnLEDMatrix(String displayText);
void setServoPosition(int position);

const int SERVO_PIN = 3;
const int SERVO_POSITION_DOWN = 0;
const int SERVO_POSITION_UP = 180;
const int SERVO_POSITION_SETUP = 90;
const int LOW_CO2_THRESHOLD = 1000;
const int HIGH_CO2_THRESHOLD = 1200;
const int SERIAL_MONITOR_BAUD_RATE = 9600;

int servoPosition = SERVO_POSITION_SETUP;

void setup()
{
  playLEDMatrixLoadingAnimation();

  // Servo Setup;
  servo.attach(SERVO_PIN);
  setServoPosition(SERVO_POSITION_SETUP);

  Serial.begin(SERIAL_MONITOR_BAUD_RATE);

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
  }
  else
  {
    Serial.println("Failed to connect to any known WiFi networks.");
  }

  // Connect to Arduino IoT Cloud

  // Defined in thingProperties.h
  initProperties();
  // FIXME: If we don't specify the network, begin() doesn't send any data.
  // However, if we are already conncected to a network, ArduinoIoTPreferredConnection doesn't seem to switch the network.
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  // Enable Debuggin of the network, IoT Cloud connection, and errors. 4 is MAX
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  // SCD30 Start
  Wire1.begin();
  while (airSensor.begin(Wire1) == false)
  {
    Serial.println("Air sensor not detected. Please check wiring. Retrying in 2 sec...");
    delay(2000);
  }

  matrix.clear();
  setServoPosition(SERVO_POSITION_UP);
  led = true;
  isLedOn = true;
}

void loop()
{
  readAndSendCO2Value();

  if (cO2Level >= HIGH_CO2_THRESHOLD)
  {
    setServoPosition(SERVO_POSITION_DOWN);
  }
  else if (cO2Level <= LOW_CO2_THRESHOLD)
  {
    setServoPosition(SERVO_POSITION_UP);
  }
}

void readAndSendCO2Value()
{
  if (airSensor.dataAvailable())
  {
    cO2Level = airSensor.getCO2();
    ArduinoCloud.update();
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

void playLEDMatrixLoadingAnimation()
{
  matrix.loadSequence(LEDMATRIX_ANIMATION_TETRIS_INTRO);
  matrix.begin();
  matrix.play(false); // false == don't repeat animation
}

void printOnLEDMatrix(String displayText)
{
  matrix.beginDraw();
  matrix.stroke(0xFFFFFFFF);
  matrix.textFont(Font_4x6);
  matrix.beginText(0, 1, 0xFFFFFF);
  matrix.println(displayText);
  matrix.endText(NO_SCROLL);
  matrix.endDraw();
}

void setServoPosition(int position)
{
  if (servoPosition == position)
  {
    return;
  }

  if (!servo.attached())
  {
    servo.attach(SERVO_PIN);
    Serial.println("Attaching servo");
  }

  Serial.println("Moving servo...");
  servoPosition = position;
  servo.write(position);
  delay(400);
  servo.detach();
}