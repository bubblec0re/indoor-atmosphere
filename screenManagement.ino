void printValues(float t, float h, float p, float c) {

  String tempStr = "T:" + (String)round(t) + "C";
  String humStr = "H:" + (String)round(h) + "%";
  String presStr = "P:" + (String)round(p) + "mm";
  String co2Str = "C:" + (String)round(c) + "ppm";

  myOLED.clrScr();
  myOLED.print(tempStr, OLED_L, 1);
  myOLED.print(humStr, OLED_L, 3);
  myOLED.print(presStr, OLED_L, 5);
  //myOLED.print("A:" + (String)(bme.readAltitude(SEALEVELPRESSURE_HPA)) + "m", OLED_L, 7);
  myOLED.print(co2Str, OLED_L, 7);
}

void connectOLED() {
  myOLED.begin();
  myOLED.setFont(MediumFont);
}
