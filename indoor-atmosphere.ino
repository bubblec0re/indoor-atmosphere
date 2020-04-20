#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <iarduino_OLED_txt.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

#define SEALEVELPRESSURE_HPA (1013.25)

//Screens
iarduino_OLED_txt myOLED(0x3C);
extern uint8_t MediumFont[];

LiquidCrystal_I2C lcd(0x27, 16, 2);

//BME
Adafruit_BME280 bme; // I2C
//MHZ-19 B
SoftwareSerial swSerial(A0, A1); // TX, RX
unsigned int ppm = 0;

void setup() {

  //Screens
  connectOLED();
//  connectLCD();

  //BME
  connectBME();

  //MHZ-19B
  connectMhz19b();
}


void loop() {
  bme.takeForcedMeasurement(); // BME goes to sleep after measuring when in Forced mode
  measureCO2();
  //printValues(bme.readTemperature(), bme.readHumidity(), (bme.readPressure() / 100.0F * 0.75006), ppm);
  printValues();
  delay(15000);
}
