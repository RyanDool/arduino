/*
  * This sketch scans WiFi networks.
  * Scanned networks are printed to oled display.
*/

// Wifi include
#include "WiFi.h"

// Display includes
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET  4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

String networksFound = " networks found";

void setup(){
  Serial.begin(115200);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){   // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);  // Don't proceed, loop forever
  }

  // Clear the display buffer
  display.clearDisplay();

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  delay(100);

  Serial.println("Setup done");
}

void loop(){
  // Set OLED text position, size, and color
  display.setCursor(1, 1);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  int n = WiFi.scanNetworks();

  if(n == 0){
    Serial.println("no" + networksFound);
    display.println("no" + networksFound);
  }else{
    Serial.println(n + networksFound);
    display.println(n + networksFound);
    display.println("");
    for(int i = 0; i < n; ++i){
      // Print SSID and RSSI for each network found
      int num = i + 1;
      String wifiSSID = WiFi.SSID(i).substring(0, 8);
      String wifiString = ": " + wifiSSID + " (" + WiFi.RSSI(i) + ")";
      Serial.println(num + wifiString);
      display.println(num + wifiString);
      delay(10);
    }
  }

  display.display();
  Serial.println("");

  // Wait 8seconds before scanning again
  delay(8000);
  
  // Clear OLED display for next scan
  display.clearDisplay();
}
