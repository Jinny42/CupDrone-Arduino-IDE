/* DigitalReadSerial

 Reads a digital input on pin PB0(8), prints the result to the serial monitor 
 You can use BOARD_BUTTON_PIN instead of using pin PB0(8) in CupDrone
 
 created 2015.10.25
 by SteamMaker
 */

void setup(){
  pinMode(BOARD_BUTTON_PIN, INPUT_PULLDOWN);
}
void loop(){
  int buttonState = digitalRead(BOARD_BUTTON_PIN);
  SerialUSB.print("buttonState = ");
  SerialUSB.println(buttonState);
  delay(100);
}


