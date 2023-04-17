#include "sensor.h"
#include "Adafruit_BME280.h"


Adafruit_BME280 bme; // create BME280 object

void setup_BME280() {
  Serial.begin(115200);
  if (!bme.begin(0x76)) { // check if BME280 is detected
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
}

void poll_BME280() {
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" *C");

  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Serial.println();
  delay(2000);
}
