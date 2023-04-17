#include <Arduino.h>
#include "wifi_connect.h"
#include "sensor.h"


void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);

  try {
    std::pair<String, String> config = getWifiCreds("/wifi.json");
    connectToWifi(config.first, config.second);

  } catch (const char* error) {
    Serial.println(error);
  }

  setup_BME280();
}


void loop() {
  poll_BME280();
  delay(5000);
}