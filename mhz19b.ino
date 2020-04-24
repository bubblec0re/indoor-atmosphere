unsigned int measureCO2() {

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

  return ppm;

}

void connectMhz19b(int tryNum)
{
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
    lcd.print("MHZ-19B Error.");
    if (tryNum < 4) {
      tryNum++;
      lcd.setCursor(0, 1);
      lcd.print("Retry " + (String)tryNum);
      delay(10000);
      connectMhz19b(tryNum);
    }
    else {
      lcd.print("MHZ-19B Error.");
      lcd.setCursor(0, 1);
      lcd.print("Cant connect");
      while (true) {
        delay(1000);
      }
    }
  }
}
