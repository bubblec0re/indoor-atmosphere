void printValues() {

  myOLED.clrScr();
  myOLED.print("T:" + (String)bme.readTemperature() + "C", OLED_L, 1);
  myOLED.print("H:" + (String)bme.readHumidity() + "%", OLED_L, 3);
  myOLED.print("P:" + (String)(bme.readPressure() / 100.0F * 0.75006) + "mm", OLED_L, 5);
  //myOLED.print("A:" + (String)(bme.readAltitude(SEALEVELPRESSURE_HPA)) + "m", OLED_L, 7);
  myOLED.print("C:" + (String)ppm + "ppm", OLED_L, 7);
}

void connectOLED() {
  myOLED.begin();
  myOLED.setFont(MediumFont);
}
<<<<<<< Updated upstream
=======

//void connectLCD() {
//  lcd.init();
//  lcd.backlight();
//}
>>>>>>> Stashed changes
