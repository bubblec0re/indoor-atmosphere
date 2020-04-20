void connectBME() {
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
}
