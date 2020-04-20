void printValues(double t, double h, double p, double c) {

  String tempStr = "T:" + (String)t + "C";
  String humStr = "H:" + (String)h + "%";
  String presStr = "P:" + (String)p + "mm";
  String co2Str = "C:" + (String)c + "ppm";

  myOLED.clrScr();
  myOLED.print(tempStr, OLED_L, 1);
  myOLED.print(humStr, OLED_L, 3);
  myOLED.print(presStr, OLED_L, 5);
  //myOLED.print("A:" + (String)(bme.readAltitude(SEALEVELPRESSURE_HPA)) + "m", OLED_L, 7);
  myOLED.print(co2Str, OLED_L, 7);

//  lcd.print(

}

void connectOLED() {
  myOLED.begin();
  myOLED.setFont(MediumFont);
}

void connectLCD() {
  lcd.init();
  lcd.backlight();
}
