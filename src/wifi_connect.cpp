#include <Arduino.h>
#include "WiFi.h"
#include "SPIFFS.h"
#include <ArduinoJson.h>
#include "wifi_connect.h"


std::pair<String, String> getWifiCreds(const char* filename) {
  if (!SPIFFS.begin(true)){
    throw "An error occurred while mounting SPIFFS";
  }

  File file = SPIFFS.open(filename);
  if (!file){
    throw "Failed to open file for reading";
  }

  size_t size = file.size();
  if (size > 1024) {
    throw "File size is too large";
  }

  std::unique_ptr<char[]> buf(new char[size]);
  file.readBytes(buf.get(), size);

  DynamicJsonDocument doc(1024);

  if (deserializeJson(doc, buf.get())) {
    throw "Failed to parse JSON data";
  }

  String ssid = doc["ssid"];
  String password = doc["password"];
  return std::make_pair(ssid, password);
}


void connectToWifi(String ssid, String password) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), password.c_str());
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}