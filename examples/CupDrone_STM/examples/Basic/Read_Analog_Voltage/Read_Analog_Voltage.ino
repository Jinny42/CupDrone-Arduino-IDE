/* Read_Analog_Voltage

 Reads an analog input on pin ?, prints the result to the serial monitor.  
 voltage = Analog_data * (Max_voltage / Max_Analog_data);
 
 created 2015.10.25
 by SteamMaker
 */

volatile float voltage=0;

void setup(){
  pinMode(1, INPUT_ANALOG);
}

void loop(){
  int AdcData = analogRead(1);
  voltage = AdcData * (3.3 / 4095.0);
  SerialUSB.print("voltage = ");
  SerialUSB.print(voltage);
  SerialUSB.println(" [V]");
  delay(100);
}

