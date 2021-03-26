/*
  SFE_BMP180 altitude example sketch

  This sketch shows how to use the Bosch BMP180 pressure sensor
  as an altimiter.
  https://www.sparkfun.com/products/11824

  Like most pressure sensors, the BMP180 measures absolute pressure.
  Since absolute pressure varies with altitude, you can use the pressure
  to determine your altitude.

  Because pressure also varies with weather, you must first take a pressure
  reading at a known baseline altitude. Then you can measure variations
  from that pressure

  Hardware connections:

  - (GND) to GND
  + (VDD) to 3.3V

  (WARNING: do not connect + to 5V or the sensor will be damaged!)

  You will also need to connect the I2C pins (SCL and SDA) to your
  Arduino. The pins are different on different Arduinos:

  Any Arduino pins labeled:  SDA  SCL
  Uno, Redboard, Pro:        A4   A5
  Mega2560, Due:             20   21
  Leonardo:                   2    3

  Leave the IO (VDDIO) pin unconnected. This pin is for connecting
  the BMP180 to systems with lower logic levels such as 1.8V

  Have fun! -Your friends at SparkFun.

  The SFE_BMP180 library uses floating-point equations developed by the
  Weather Station Data Logger project: http://wmrx00.sourceforge.net/

  Our example code uses the "beerware" license. You can do anything
  you like with this code. No really, anything. If you find it useful,
  buy me a beer someday.

  V10 Mike Grusin, SparkFun Electronics 10/24/2013
  V1.1.2 Updates for Arduino 1.6.4 5/2015
*/

#include "InfiSense.h"
#include "InfiCloud.h"
#include "InfiSense_LCD.h"
#include <Arduino_JSON.h>

#define TOKEN "1c6e4c8e-256e-4077-bcd3-cc4ff99d44e0" // Put here your InfiIoT TOKEN
#define WIFI_SSID "InfiIoT Technologies"                    // Put here your Wi-Fi SSID
#define WIFI_PASSWORD "18072020"                // Put here your Wi-Fi password
//#define WIFI_SSID "OnePlus 5"                    // Put here your Wi-Fi SSID
//#define WIFI_PASSWORD "9876543210"                // Put here your Wi-Fi password
//#define WIFI_SSID "INFINITY"                    // Put here your Wi-Fi SSID
//#define WIFI_PASSWORD "        "                // Put here your Wi-Fi password
#define HOST_ADDRESS "https://infiiot.com/api/v1.0/update-Variable-multiple"
#define RECEIVE_ADDRESS "https://infiiot.com/api/v1.0/get-Variable-lv"

#define DEVICE_NAME "InfiSense"

InfiSense agri;
InfiCloud client(TOKEN, DEVICE_NAME);

boolean DEBUG_InfiSense = false;

void setup()
{
  Serial.begin(9600);
  agri.begin(DEBUG_InfiSense);
  // display.begin(3);
  client.setDebug(false);
  client.attachLEDToStatus(true);

  LcdDisplayInit();
  // setLcdScreens();
}

void loop()
{
  updateLcdDisplay(4, 5000); //3 screens update every 5 seconds
  getDataEvery(500); //get data from infiiot platform after specific interval
  sendDataEvery(5 * 60000); // send data after every 1 minute
}

/*timing calculations done using following variables*/
long int prevMillisForSend = 0;
long int prevMillisForGet = 0;
long int currMillisCloud = 0;

void sendDataEvery(long nextSendTime)
{
  currMillisCloud = millis();
  if (currMillisCloud - prevMillisForSend >= nextSendTime) //Maintenance Routine
  {
    Serial.println("Sending data");
    float soil_mositure = agri.readSoilSensor();
    float temperature = agri.readDS18B20();
    float UVIndex = agri.readUVSensor();
    // agri.readML8511();
    float Leaf = agri.readLeafSensor();
    float rain =  agri.readRainSensor();
    float alt = agri.readBMEAltitude();
    float AirHumidity = agri.readBMEAirHumidity();
    float AirPressure = agri.readBMEAirPressure();
    float AirTemp = agri.readBMEAirTemp();
    float Light = agri.readLUXSensor();
    // agri.readBH1750();
    // agri.triggerPump(1);
    // agri.readBatteryVoltage();
    // agri.triggerPumpOn();
    // agri.triggerLedOn();
    // delay(3000);
    // agri.triggerPumpOff();
    // agri.triggerLedOff();
    // delay(1000);
    // agri.turnLEDOn();
    // delay(1000);
    // agri.turnLEDOff();
    // delay(1000);

    client.connectToWiFi(WIFI_SSID, WIFI_PASSWORD);
    client.add("Soil_Temp", temperature);
    client.add("Soil_Moisture", soil_mositure);
    client.add("UVIndex", UVIndex);
    client.add("Rain", rain);
    client.add("Leaf", Leaf);
    client.add("Altitude", alt);
    client.add("Air_Humidity", AirHumidity);
    client.add("Air_Pressure", AirPressure);
    client.add("Air_Temp", temperature);
    client.add("Light_Intensity", Light);
    client.makePayload();
    client.sendToCloud(HOST_ADDRESS);

    prevMillisForSend = currMillis;
    Serial.println("Data Sent");
  }
}

String Rxpayload = "";
void getDataEvery(long nextSendTime)
{
  currMillisCloud = millis();
  if (currMillisCloud - prevMillisForGet >= nextSendTime) //Maintenance Routine
  {
    client.connectToWiFi(WIFI_SSID, WIFI_PASSWORD);
    delay(100);
    client.get("InfiSense", "Pump_Control");
    Rxpayload = client.getFromCloud(RECEIVE_ADDRESS);

    if (getKeyFromPayload("value") >= 1)
    {
      agri.triggerPumpOn();
    }
    else if (getKeyFromPayload("value") == 0)
    {
      agri.triggerPumpOff();
    }
    else if (getKeyFromPayload("value") <= 0)
    {
      agri.triggerPumpOff();
    }
    else
    {
      agri.triggerPumpOff();
    }

    prevMillisForGet = currMillis;
  }
}

int getKeyFromPayload(char *key)
{
  JSONVar myObject = JSON.parse(Rxpayload);

  if (JSON.typeof(myObject) == "undefined")
  {
    Serial.println("Parsing input failed!");
    return -1;
  }

  if (myObject.hasOwnProperty(key))
  {
    int x = (int)(myObject[key]);
    Serial.printf("Got Value: %d\n", x);
    return x;
  }
}
