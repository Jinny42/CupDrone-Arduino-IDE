//----------------------------------------------------------------------------
//    ?�로그램�?	: 
//
//    만든??    	: Cho Han Cheol 
//
//    ?? �?    : 
//    
//    최종 ?�정  	: 
//
//    MPU_Type	: 
//
//    ?�일�?    	: MSP_Cmd.ino
//----------------------------------------------------------------------------




#include <Arduino.h> 

#include "MSP_Cmd.h"




#define MSP_CMD_START			'$'
#define MSP_CMD_HEADER_M		'M'
#define MSP_CMD_HEADER_ARROW 	'<'



#define MSP_CMD_STATE_WAIT_START			0
#define MSP_CMD_STATE_WAIT_HEADER_M			1
#define MSP_CMD_STATE_WAIT_HEADER_ARROW		2
#define MSP_CMD_STATE_WAIT_DATA_SIZE		3
#define MSP_CMD_STATE_WAIT_CMD				4
#define MSP_CMD_STATE_WAIT_DATA				5
#define MSP_CMD_STATE_WAIT_CHECKSUM			6







/*---------------------------------------------------------------------------
     TITLE   : MSP_Cmd
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
MSP_Cmd::MSP_Cmd()
{
	Cmd_State = MSP_CMD_STATE_WAIT_START;
}





/*---------------------------------------------------------------------------
     TITLE   : begin
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
// CupDrone(Reo)
void MSP_Cmd::begin()
{
	pSerial = &Serial1;
	Serial1.begin(115200);			
}

// CupDrone(STM) 
/*void MSP_Cmd::begin( uint8_t uart_num )
{
	//-- ?�신 ?�트 초기?? 
	//
	switch( uart_num )
	{
		case 1:
			pSerial = &Serial1;
			Serial1.begin(115200);	
			break;

		case 2:
			pSerial = &Serial2;
			Serial2.begin(115200);	
			break;

		default:
			pSerial = &Serial1;
			Serial1.begin(115200);			
			break;
	}
	
}*/





/*---------------------------------------------------------------------------
     TITLE   : update
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
bool MSP_Cmd::update( void )
{
	bool    Ret = false;
	uint8_t ch;


	//-- 명령???�신
	//
	if( pSerial->available() )
	{
		ch = pSerial->read();
	}
	else
	{
		return false;
	}

	//Serial.write(ch);


	//-- 바이?�간 ?�?�아???�정(200ms)
	//
	CurrentTime = micros();

	if( (CurrentTime - PreviousTime) > 200000 )
	{
		Cmd_State    = MSP_CMD_STATE_WAIT_START;
		PreviousTime = CurrentTime;
	}	



	//-- 명령???�태
	//
	switch( Cmd_State )
	{

		//-- ?�작 문자 기다리는 ?�태 
		//
		case MSP_CMD_STATE_WAIT_START:

			// ?�작 문자�?기다�?			if( ch == MSP_CMD_START )
			{
				Cmd_State    = MSP_CMD_STATE_WAIT_HEADER_M;
			}
			break;


		//-- 'M' 기다리는 ?�태 
		//
		case MSP_CMD_STATE_WAIT_HEADER_M:
			if( ch == MSP_CMD_HEADER_M )
			{
				Cmd_State = MSP_CMD_STATE_WAIT_HEADER_ARROW;				
			}
			else
			{
				Cmd_State = MSP_CMD_STATE_WAIT_START;
			}
			break;


		//-- '<' 기다리는 ?�태 
		//
		case MSP_CMD_STATE_WAIT_HEADER_ARROW:
			if( ch == MSP_CMD_HEADER_ARROW )
			{
				Cmd.CheckSum = 0x00;
				Cmd.Length   = 0;				
				Cmd_State = MSP_CMD_STATE_WAIT_DATA_SIZE;				
			}
			else
			{
				Cmd_State = MSP_CMD_STATE_WAIT_START;
			}
			break;


				Cmd.CheckSum = 0x00;
				Cmd.Length   = 0;


		//-- ?�이???�이�?기다리는 ?�태(64까�?)
		//
		case MSP_CMD_STATE_WAIT_DATA_SIZE:

			if( ch <= MSP_CMD_MAX_LENGTH )
			{
				Cmd.Length    = ch;
				Index_Data    = 0;
				Cmd.CheckSum ^= ch;
				Cmd_State     = MSP_CMD_STATE_WAIT_CMD;
			}
			else
			{
				Cmd_State = MSP_CMD_STATE_WAIT_START;	
			}
			break;


		//-- 명령?��? 기다리는 ?�태
		//
		case MSP_CMD_STATE_WAIT_CMD:

			Cmd.Cmd       = ch;
			Cmd.CheckSum ^= ch;

			if( Cmd.Length == 0 )
			{
				Cmd_State = MSP_CMD_STATE_WAIT_CHECKSUM;
			}
			else
			{
				Cmd_State = MSP_CMD_STATE_WAIT_DATA;
			}
			break;


		//-- ?�이?��? 기다리는 ?�태
		//
		case MSP_CMD_STATE_WAIT_DATA:
			
			Cmd.CheckSum          ^= ch;
			Cmd.Data[ Index_Data ] = ch;

			Index_Data++;

			if( Index_Data >= Cmd.Length )
			{
				Cmd_State = MSP_CMD_STATE_WAIT_CHECKSUM;
			} 
			break;


		//-- 체크?�을 기다리는 ?�태
		//
		case MSP_CMD_STATE_WAIT_CHECKSUM:

			if( Cmd.CheckSum == ch )
			{
				Ret = true;
			}

			Cmd_State = MSP_CMD_STATE_WAIT_START;		
			break;
	}

	return Ret;
}





/*---------------------------------------------------------------------------
     TITLE   : Get_CmdPtr
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
MSP_CMD_OBJ *MSP_Cmd::Get_CmdPtr( void )
{
	return &Cmd;
}





/*---------------------------------------------------------------------------
     TITLE   : Get_RespPtr
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
MSP_RESP_OBJ *MSP_Cmd::Get_RespPtr( void )
{
	return &Resp;
}





/*---------------------------------------------------------------------------
     TITLE   : SendReap
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void MSP_Cmd::SendResp( MSP_RESP_OBJ *pResp )
{
	uint8_t i;
	uint8_t CheckSum = 0;


	pSerial->write( MSP_CMD_START );
	pSerial->write( MSP_CMD_HEADER_M );

	if( pResp->ErrorCode > 0 )	pSerial->write('!');
	else						pSerial->write('>');

	pSerial->write( pResp->Length );		
	pSerial->write( pResp->Cmd );		CheckSum ^= pResp->Cmd;

	for( i=0; i<pResp->Length; i++ )
	{
		pSerial->write( pResp->Data[i] );
		CheckSum ^= pResp->Data[i];		
	}

	pSerial->write( CheckSum );
}


