/*
*  Example   of CupDrone Reo
*  Made by SteamMaker 2015.12.26
*  www.steammaker.co.kr
*/

#include <Servo.h>

Servo myservo

float angle;

int startFlag =0;
float pi = 3.141592;
float ts = 0.001 * 0.001;
unsigned long tCount = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attatch(9);
}

void loop() {
  // put your main code here, to run repeatedly:

}
