#include <Arduino.h>
#include "WiFi.h"
#include "SPIFFS.h"
#include <ArduinoJson.h>


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


std::pair<String, String> foo(const char* filename) {
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
  auto error = deserializeJson(doc, buf.get());

  if (error) {
    throw "Failed to parse JSON data";
  }

  String ssid = doc["ssid"];
  String password = doc["password"];
  return std::make_pair(ssid, password);
}


void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);


  try {
    std::pair<String, String> config = foo("/wifi.json");
    connectToWifi(config.first, config.second);

  } catch (const char* error) {
    Serial.println(error);
  }  
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000); // LED will be on for 1000 milliseconds (1 second)
  digitalWrite(LED_BUILTIN, LOW);
  delay(5000); // LED will be off for 1000 milliseconds (1 second)
  }