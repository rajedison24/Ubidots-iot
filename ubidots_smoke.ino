#include <BearSSLHelpers.h>
#include <CertStoreBearSSL.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiClientSecureAxTLS.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiServer.h>
#include <WiFiServerSecure.h>
#include <WiFiServerSecureAxTLS.h>
#include <WiFiServerSecureBearSSL.h>
#include <WiFiUdp.h>
#include "Ubidots.h"
const char* UBIDOTS_TOKEN = "BBFF-GqL7UGpRkrujULKz6Ym7BSWYcJDDL8";  // Put here your Ubidots TOKEN
const char* WIFI_SSID = "OnePlus"; // Put here your Wi-Fi SSID
const char* WIFI_PASS = "12345678"; // Put here your Wi-Fi password

Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);
void setup() {
  Serial.begin(115200);
  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS);

  // ubidots.setDebug(true);  // Uncomment this line for printing debug messages
}

void loop() {
  float smoke = analogRead(A0);
  Serial.println(smoke);
  ubidots.add("PPM", smoke);  // Change for your variable name
  bool bufferSent = false;
  bufferSent = ubidots.send();  // Will send data to a device label that matches the device Id

  if (bufferSent) {
    // Do something if values were sent properly
    Serial.println("Values sent by the device");
  }

  delay(5000);
}
