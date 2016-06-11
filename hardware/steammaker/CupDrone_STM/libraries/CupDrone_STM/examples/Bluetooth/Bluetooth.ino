/* Bluetooth Comunication 

Example for CupDrone STM
created 2016. 02. 17
 by www.steammaker.co.kr
 */
 
 
void setup() {
  // put your setup code here, to run once:
  SerialUSB.begin();
  Serial2.begin(115200);  
}

void loop() {
  // put your main code here, to run repeatedly:
  // Serial1 –> Data –> Serial
  if (Serial2.available()) {
    SerialUSB.print((char)Serial2.read());
  }

  // Serial –> Data –> Serial1
  if (SerialUSB.available()) {
    Serial2.print((char)SerialUSB.read());
  }
}
