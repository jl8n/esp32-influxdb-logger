#include <Arduino.h>
#include "wifi_connect.h"
#include "BME280_helper.h"
#include "send_data.h"


void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);

  try {
    std::pair<String, String> config = getWifiCreds("/config.json");
    connectToWifi(config.first, config.second);

  } catch (const char* error) {
    Serial.println(error);
  }

  setup_BME280();

}


void loop() {
  SensorData data = poll_BME280();
  sendData(data);
  delay(1000 * 60 * 5);  // 5 minutes
}