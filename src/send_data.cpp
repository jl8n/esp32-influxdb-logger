#include <Arduino.h>
#include <ArduinoJson.h>
#include "WiFi.h"
#include "SPIFFS.h"
#include "ServerInfo.h"
#include "send_data.h"


ServerInfo getServerInfo(const char* filename) {
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

  ServerInfo server = { doc["url"], doc["port"], doc["endpoint"], doc["influx_api_key"] };
  return server;
}


String constructJsonBody(SensorData data) {
  const int capacity = JSON_OBJECT_SIZE(4);
  StaticJsonDocument<capacity> jsonDoc;
  jsonDoc["room"] = 1; // needs to be unique per ESP32 board
  jsonDoc["temperature"] = data.temperature;
  jsonDoc["humidity"] = data.humidity;
  jsonDoc["pressure"] = data.pressure;
  String jsonString;
  serializeJson(jsonDoc, jsonString);
  return jsonString;
}


void sendData(SensorData data) {
  const char* configFile = "/config.json";
  ServerInfo serverInfo = getServerInfo(configFile);
  //String jsonString = "{\"name\":\"John\", \"age\":30}";
  String dataString = "sensor_data,room=bedroom temperature=" + String(data.temperature) + ",humidity=" + String(data.humidity) + ",pressure=" + String(data.pressure);

  Serial.println(serverInfo.url + serverInfo.port + serverInfo.endpoint);
  Serial.println(dataString);
  WiFiClient client;

  if (client.connect(serverInfo.url.c_str(), serverInfo.port)) {
    client.print("POST " + serverInfo.endpoint + " HTTP/1.1\r\n");
    client.print("Host: " + serverInfo.url + "\r\n");
    client.print("Authorization: Token " + serverInfo.influx_api_key + "\r\n");
    client.print("Content-Type: text/plain\r\n");
    client.print("Content-Length: " + String(dataString.length()) + "\r\n");
    client.print("\r\n");
    client.print(dataString);

    // Wait for the server to respond
    if (client.available()) {
      String line = client.readStringUntil('\r');
      Serial.println(line);
    }
  }
}