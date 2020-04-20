void connectBME() {
  unsigned status;
  status = bme.begin(0x76);
  if (!status) {
    lcd.print("BME Error");
    lcd.setCursor(0,1);
    lcd.print(bme.sensorID());
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
