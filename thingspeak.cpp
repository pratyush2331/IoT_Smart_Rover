// ------style guard ----

#ifdef __cplusplus

extern "C"

{

#endif

uint8_t temprature_sens_read();

#ifdef __cplusplus

}

#endif

uint8_t temprature_sens_read();

// ------header files----

#include <ESP8266WiFi.h>

#include "ThingSpeak.h"

#include <Wire.h>

#include <Adafruit_BMP280.h>

#define BMP_SDA 2

#define BMP_SCL 1

Adafruit_BMP280 bmp280;

// -----netwrok credentials

char* ssid = "Galaxy M312B5A"; // your network SSID (name)

const char* password = "00000000"; // your network password

WiFiClient client;

// -----ThingSpeak channel details

unsigned long myChannelNumber = 3;

const char * myWriteAPIKey = "UJL0LBCMD5AY744T";

// ----- Timer variables

unsigned long lastTime = 0;

unsigned long timerDelay = 1000;

void setup() {
  Serial.begin(115200); // Initialize serial

Serial.println("Initializing BMP280");

boolean status = bmp280.begin(0x76);

if (!status)

{

Serial.println("Not connected");

}

//Initialize Wi-Fi

WiFi.begin(ssid, password);

Serial.print("Connecting to Wi-Fi");

while (WiFi.status() != WL_CONNECTED)

{

Serial.print(".");

delay(100);

}

Serial.println();

Serial.print("Connected with IP: ");

Serial.println(WiFi.localIP());

Serial.println();

// Initialize ThingSpeak

ThingSpeak.begin(client);

}

void loop() {
  
  if ((millis() - lastTime) > timerDelay )

{

float temp = bmp280.readTemperature(); //temperature measurement

Serial.print("temperature: ");

Serial.print(temp);

Serial.println("*C");

float altitude = bmp280.readAltitude(1011.18); //altitude measurement

Serial.print("Altitude: ");

Serial.print(altitude);

Serial.println("m");

float pressure = (bmp280.readPressure()/100); //pressure measurement

Serial.print("Pressure: ");

Serial.print(pressure);

Serial.println("hPa");

Serial.println(" ");

ThingSpeak.setField(1, temp );

ThingSpeak.setField(2, altitude);

ThingSpeak.setField(3, pressure);

// Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different

// pieces of information in a channel. Here, we write to field 1.

int x = ThingSpeak.writeFields(myChannelNumber,

myWriteAPIKey );

if(x == 200)

{

Serial.println("Channel update successful." );

}

else

{

Serial.println("Problem updating channel. HTTP error code " + String(x) );

}

lastTime = millis();

}

}
