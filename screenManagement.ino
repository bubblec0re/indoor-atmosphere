void printValues(unsigned int t, unsigned int h, unsigned int p, unsigned int c) {

  String tempStr = "T:" + (String)t + "C";
  String humStr = "H:" + (String)h + "%";
  String presStr = "P:" + (String)p + "mm";
  String co2Str = "C:" + (String)c + "ppm";

  lcd.clear();

  lcd.print(tempStr);

  lcd.setCursor(7, 0);
  lcd.print(humStr);

  lcd.setCursor(0, 1);
  lcd.print(presStr);

  lcd.setCursor(7, 1);
  lcd.print(co2Str);
}

void connectLCD() {
  lcd.init();
  lcd.backlight();
}

void toggleBacklight() {
  backlight_on = !backlight_on;
  lcd.setBacklight(backlight_on);
}
