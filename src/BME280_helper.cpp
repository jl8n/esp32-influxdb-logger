#include "Adafruit_BME280.h"
#include "BME280_helper.h"



Adafruit_BME280 bme; // create BME280 object

void setup_BME280() {
  Serial.begin(115200);
  if (!bme.begin(0x76)) { // check if BME280 is detected
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
}

SensorData poll_BME280() {
  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure() / 100.0F;

  SensorData data = { temperature, humidity, pressure };

  return data;
}
