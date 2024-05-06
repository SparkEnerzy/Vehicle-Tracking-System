#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include "ThingSpeak.h"
TinyGPSPlus gps;
SoftwareSerial ss(D4,D3); //D3-RX D4-TX

const char* ssid = "poweriot";
const char* password = "1234567890";
String lng_str,lat_str;
unsigned long myChannelNumber = 1927677;
const char * myWriteAPIKey = "RRFG7AV1S6RFQTLL";
WiFiClient  client;
WiFiServer server(80);
void setup()
{
  Serial.begin(9600);
  ss.begin(9600);
  Serial.println();
  Serial.print("Connecting");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client);
}

void loop()
{
  while (ss.available() > 0)
while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
      Serial.print("Latitude= "); 
      Serial.print(gps.location.lat(), 6);
      Serial.print(" Longitude= "); 
      Serial.println(gps.location.lng(), 6);
      lng_str=String(gps.location.lng(),6);
      lat_str=String(gps.location.lat(),6);
      ThingSpeak.setField(1,lng_str );
        ThingSpeak.setField(2,lat_str );
        ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    }
  }
}
