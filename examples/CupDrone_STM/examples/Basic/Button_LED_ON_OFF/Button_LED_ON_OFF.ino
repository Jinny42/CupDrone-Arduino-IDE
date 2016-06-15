void setup(){
  pinMode(BOARD_LED0_PIN, OUTPUT);
  pinMode(BOARD_BUTTON_PIN, INPUT_PULLDOWN);
}
void loop(){
  int buttonState = digitalRead(BOARD_BUTTON_PIN);
  
  if(buttonState == HIGH) {
    digitalWrite(BOARD_LED0_PIN, HIGH);
  }else {
    digitalWrite(BOARD_LED0_PIN, LOW);
  }  
  delay(100);
}
