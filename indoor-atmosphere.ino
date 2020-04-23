
#include <GyverBME280.h>
#include <SoftwareSerial.h>
#include <microLiquidCrystal_I2C.h>

//Screen
LiquidCrystal_I2C lcd(0x27, 16, 2);

//BME
GyverBME280 bme;

//MHZ-19 B
SoftwareSerial swSerial(A0, A1); // TX, RX

unsigned int ppm = 0, temp = 0, humid = 0, pres = 0;
unsigned int lastValues[4] = {0, 0, 0, 0};

void setup() {

  //Screens
  connectLCD();

  //BME
  connectBME();

  //MHZ-19B
  connectMhz19b();
}


void loop() {

  bme.oneMeasurement(); // BME goes to sleep after measuring when in Forced mode

  temp = round(bme.readTemperature());
  humid = round(bme.readHumidity());
  pres = round(pressureToMmHg(bme.readPressure()));
  ppm = measureCO2();

  if (temp != lastValues[0] || humid != lastValues[1] || pres != lastValues[2] || ppm != lastValues[3]) {

    lastValues[0] = temp;
    lastValues[1] = humid;
    lastValues[2] = pres;
    lastValues[3] = ppm;

    printValues(temp, humid, pres, ppm);
  }

  delay(15000);

}
