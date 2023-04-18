#include <Arduino.h>
#include "wifi_connect.h"
#include "BME280_helper.h"
#include "send_data.h"
#include "oled_display.h"


void setup() {
  Serial.begin(115200);

  try {
    std::pair<String, String> config = getWifiCreds("/config.json");
    connectToWifi(config.first, config.second);
    setup_BME280();
    init_oled();

  } catch (const char* error) {
    Serial.println(error);
  }
}


void loop() {
  SensorData data = poll_BME280();
  sendData(data);
  drawSensorData(data);
  delay(1000 * 60 * 5);  // 5 minutes
}