//----------------------------------------------------------------------------
//    ?๋ก๊ทธ๋จ๋ช?	: 
//
//    ๋ง๋ ??    	: Cho Han Cheol 
//
//    ?? ์ง?    : 
//    
//    ์ต์ข ?์   	: 
//
//    MPU_Type	: 
//
//    ?์ผ๋ช?    	: MSP_Cmd.ino
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
	//-- ?ต์  ?ฌํธ ์ด๊ธฐ?? 
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


	//-- ๋ช๋ น???์ 
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


	//-- ๋ฐ์ด?ธ๊ฐ ??์???ค์ (200ms)
	//
	CurrentTime = micros();

	if( (CurrentTime - PreviousTime) > 200000 )
	{
		Cmd_State    = MSP_CMD_STATE_WAIT_START;
		PreviousTime = CurrentTime;
	}	



	//-- ๋ช๋ น???ํ
	//
	switch( Cmd_State )
	{

		//-- ?์ ๋ฌธ์ ๊ธฐ๋ค๋ฆฌ๋ ?ํ 
		//
		case MSP_CMD_STATE_WAIT_START:

			// ?์ ๋ฌธ์๋ฅ?๊ธฐ๋ค๋ฆ?			if( ch == MSP_CMD_START )
			{
				Cmd_State    = MSP_CMD_STATE_WAIT_HEADER_M;
			}
			break;


		//-- 'M' ๊ธฐ๋ค๋ฆฌ๋ ?ํ 
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


		//-- '<' ๊ธฐ๋ค๋ฆฌ๋ ?ํ 
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


		//-- ?ฐ์ด???ฌ์ด์ฆ?๊ธฐ๋ค๋ฆฌ๋ ?ํ(64๊น์?)
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


		//-- ๋ช๋ น?ด๋? ๊ธฐ๋ค๋ฆฌ๋ ?ํ
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


		//-- ?ฐ์ด?ฐ๋? ๊ธฐ๋ค๋ฆฌ๋ ?ํ
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


		//-- ์ฒดํฌ?ฌ์ ๊ธฐ๋ค๋ฆฌ๋ ?ํ
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


