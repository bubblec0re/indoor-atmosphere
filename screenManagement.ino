void printValues(unsigned int t, unsigned int h, unsigned int p, unsigned int c) {

  String tempStr = "T:" + (String)t + "C";
  String humStr = "H:" + (String)h + "%";
  String presStr = "P:" + (String)p + "mm";
  String co2Str = "C:" + (String)c + "ppm";

  lcd.print(tempStr);

  lcd.setCursor(8, 0);
  lcd.print(humStr);

  lcd.setCursor(0, 1);
  lcd.print(presStr);

  lcd.setCursor(8, 1);
  lcd.print(co2Str);
}

void connectLCD() {
  lcd.init();
  lcd.backlight();
}
