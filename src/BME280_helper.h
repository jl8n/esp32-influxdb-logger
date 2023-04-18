#ifndef BME280_HELPER_H
#define BME280_HELPER_H

#include "Adafruit_BME280.h"


struct SensorData {
  float temperature;
  float humidity;
  float pressure;
};

void setup_BME280();
SensorData poll_BME280();
float celsiusToFahrenheit(float celsius);
float pressureToAltitude(float airPressure);


#endif /* BME280_HELPER_H */
