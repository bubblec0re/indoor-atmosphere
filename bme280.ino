void connectBME() {
  unsigned status;
  bme.setMode(FORCED_MODE);
  status = bme.begin(0x76);
  if (!status) {
    lcd.print("BME Error");
    lcd.setCursor(0,1);
    while (1) {
      delay(10000);
    };
  };
}
