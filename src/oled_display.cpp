#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "oled_display.h"
#include "BME280_helper.h"

#define SCREEN_WIDTH 128   // OLED display width,  in pixels
#define SCREEN_HEIGHT 64   // OLED display height, in pixels
#define OLED_RESET -1      // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void init_oled () {
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("OLED allocation failed"));
    while (true);  // Don't proceed, loop forever
  }
}


void drawDegreesSymbol(int16_t radius) {
  // Draw a circle (degree symbol) at the current cursor location
  int16_t width = display.getCursorX();
  int16_t x = width + 2;  // create a little whitespace after last character
  int16_t y = display.getCursorY() + radius; // move degree symbol up
  display.drawCircle(x, y, radius, WHITE);
}


void drawSensorData(SensorData data) {
  display.clearDisplay();
  display.setRotation(2);  // rotate the display 180 degrees
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);  // Start at top-left corner

  // celsius + degree symbol
  display.print(data.temperature);
  drawDegreesSymbol(2);
  display.setTextSize(1);
  display.print("  C");
  display.setTextSize(2);
  display.print("\n");

  // fahrenheit + degree symbol
  display.print(celsiusToFahrenheit(data.temperature));
  drawDegreesSymbol(2);
  display.setTextSize(1);
  display.print("  F");
  display.setTextSize(2);
  display.print("\n");
  
  // humidity + %
  display.print(String(data.humidity));
  display.setTextSize(1);
  display.print(" %");
  display.setTextSize(2);
  display.print("\n");

  // pressure + hPa
  display.print(String(data.pressure));
  display.setTextSize(1);
  display.println(" hPa");

  display.display(); 
}

