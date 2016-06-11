/*
    Example for CupDrone Reo
    Made by Baram 2015. 8.22
    Modified by SteamMaker 2106.01.10
    www.steammaker.co.kr 
*/

#include "MSP_Cmd.h"
#include "MSP.h"

MSP	Remote;

void setup()
{
  Serial.begin(9600);
  Remote.begin();
}


void loop()
{
  if ( Remote.update() == true )
  {
    Serial.print( Remote.Get_Roll() ); 		Serial.print( "\t" );
    Serial.print( Remote.Get_Pitch() ); 	Serial.print( "\t" );
    Serial.print( Remote.Get_Yaw() ); 		Serial.print( "\t" );
    Serial.print( Remote.Get_Throtle() ); 	Serial.print( "\t" );
    Serial.println(" ");

  }
}
