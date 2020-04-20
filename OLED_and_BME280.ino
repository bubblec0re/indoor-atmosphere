#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <iarduino_OLED_txt.h>
#include <SoftwareSerial.h>

#define SEALEVELPRESSURE_HPA (1013.25)

//Screen
iarduino_OLED_txt myOLED(0x3C);
extern uint8_t MediumFont[];
//BME
Adafruit_BME280 bme; // I2C
//MHZ-19 B
SoftwareSerial swSerial(A0, A1); // TX, RX
unsigned int ppm = 0;

void setup() {

  //Screen
  myOLED.begin();
  myOLED.setFont(MediumFont);

  //BME
  unsigned status;
  status = bme.begin(0x76);
  if (!status) {
    myOLED.print("BME Error", OLED_L, 1);
    myOLED.print(bme.sensorID(), OLED_L, 3);
    while (1) {
      delay(10000);
    };
  };

  bme.setSampling(Adafruit_BME280::MODE_FORCED,
                  Adafruit_BME280::SAMPLING_X1, // temperature
                  Adafruit_BME280::SAMPLING_X1, // pressure
                  Adafruit_BME280::SAMPLING_X1, // humidity
                  Adafruit_BME280::FILTER_OFF);


  //MHZ-19B
  swSerial.begin(9600);
  //Источник - https://revspace.nl/MHZ19
  byte setrangeA_cmd[9] = {0xFF, 0x01, 0x99, 0x00, 0x00, 0x00, 0x13, 0x88, 0xCB}; // задаёт диапазон 0 - 5000ppm
  unsigned char setrangeA_response[9];
  swSerial.write(setrangeA_cmd, 9);
  swSerial.readBytes(setrangeA_response, 9);
  int setrangeA_i;
  byte setrangeA_crc = 0;
  for (setrangeA_i = 1; setrangeA_i < 8; setrangeA_i++) setrangeA_crc += setrangeA_response[setrangeA_i];
  setrangeA_crc = 255 - setrangeA_crc;
  setrangeA_crc += 1;
  if (!(setrangeA_response[0] == 0xFF && setrangeA_response[1] == 0x99 && setrangeA_response[8] == setrangeA_crc) ) {
    myOLED.print("MHZ-19B Error", OLED_L, 1);
  }
}


void loop() {
  bme.takeForcedMeasurement(); // BME goes to sleep after measuring when in Forced mode
  measureCO2();
  printValues();
  delay(15000);
}

void printValues() {

  myOLED.clrScr();
  myOLED.print("T:" + (String)bme.readTemperature() + "C", OLED_L, 1);
  myOLED.print("H:" + (String)bme.readHumidity() + "%", OLED_L, 3);
  myOLED.print("P:" + (String)(bme.readPressure() / 100.0F * 0.75006) + "mm", OLED_L, 5);
  //myOLED.print("A:" + (String)(bme.readAltitude(SEALEVELPRESSURE_HPA)) + "m", OLED_L, 7);
  myOLED.print("C:" + (String)ppm + "ppm", OLED_L, 7);
}

void measureCO2() {

  byte measure_cmd[9] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};
  unsigned char measure_response[9];

  // ***** узнаём концентрацию CO2 через UART: *****
  swSerial.write(measure_cmd, 9);
  swSerial.readBytes(measure_response, 9);
  int i;
  byte crc = 0;
  for (i = 1; i < 8; i++) crc += measure_response[i];
  crc = 255 - crc;
  crc += 1;
  if ( !(measure_response[0] == 0xFF && measure_response[1] == 0x86 && measure_response[8] == crc) ) {
    ppm = 0;
  }
  unsigned int responseHigh = (unsigned int) measure_response[2];
  unsigned int responseLow = (unsigned int) measure_response[3];
  ppm = (256 * responseHigh) + responseLow;

}
