/*
*  Example of CupDrone Reo
*  Made by SteamMaker 2015.12.26
*  www.steammaker.co.kr
*/

#define M1   10
#define M2    6
#define M3    5
#define M4    9


void setup() {
  // put your setup code here, to run once:
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(M3, OUTPUT);
  pinMode(M4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);

  analogWrite(M1, 10);
  analogWrite(M2, 10);
  analogWrite(M3, 50);
  analogWrite(M4, 50); 

  delay(2000);

  analogWrite(M1, 50);
  analogWrite(M2, 50);
  analogWrite(M3, 10);
  analogWrite(M4, 10); 

  delay(2000);

  while (1) {
    analogWrite(M1, 0);
    analogWrite(M2, 0);
    analogWrite(M3, 0);
    analogWrite(M4, 0);
  }
}


