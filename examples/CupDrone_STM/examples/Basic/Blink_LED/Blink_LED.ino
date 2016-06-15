/* Blink(LED)
 
 Turns on the built-in LED(Status LED) on for 0.1 second, then off for 0.1 second,
 repeatedly. BOARD_LED_PIN is defined previously, so just use it without declaration.
 BOARD_LED_PIN was connected to connected to pin PB4(17) in CupDrone.

 created 2015.10.25
 by SteamMaker 
 */


void setup() {
  pinMode(BOARD_LED0_PIN, OUTPUT);
  pinMode(BOARD_LED1_PIN, OUTPUT);  
}


void loop() {
  digitalWrite(BOARD_LED0_PIN, HIGH);   
  digitalWrite(BOARD_LED1_PIN, LOW);   
  delay(500);            
  digitalWrite(BOARD_LED0_PIN, LOW);
  digitalWrite(BOARD_LED1_PIN, HIGH);   
  delay(500);            
}
