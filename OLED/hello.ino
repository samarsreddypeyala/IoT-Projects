
 #include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET D5
Adafruit_SSD1306 display(OLED_RESET);

// Initialize DHT sensor


void setup() {
  Wire.begin();
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);// initialize with the I2C addr 0x3C
}
 
void loop() {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(30,0);
  display.print("Astronics 3.0");
  display.display();
}
