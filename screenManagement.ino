void printValues(float t, float h, float p, float c) {

  String tempStr = "T:" + (String)round(t) + "C";
  String humStr = "H:" + (String)round(h) + "%";
  String presStr = "P:" + (String)round(p) + "mm";
  String co2Str = "C:" + (String)round(c) + "ppm";

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
