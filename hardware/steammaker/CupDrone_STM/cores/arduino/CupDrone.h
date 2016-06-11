/*
 * The MIT License
 *
 * Copyright (c) 2011 LeafLabs, LLC.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/


/*
 * CupDrone.h
 *
 *  Created on: 2015. 08. 22.
 *      Author: Baram
 *      ported from maple.h(leaflabs.com)
 *      @brief  
 */
#ifndef CUPDRONE_H_
#define CUPDRONE_H_

//#include "gpio.h"


#define CYCLES_PER_MICROSECOND  72
#define SYSTICK_RELOAD_VAL      71999 /* takes a cycle to reload */

#define BOARD_BUTTON_PIN         8//PB0
#define BOARD_LED_PIN           17//PB4

#define BOARD_LED0_PIN          17//PB4
#define BOARD_LED1_PIN          28//PB5


/* V1.5
#define BOARD_PWM_M0          	6    
#define BOARD_PWM_M1          	30
#define BOARD_PWM_M2          	7
#define BOARD_PWM_M3          	9
*/

// V2.0
#define BOARD_PWM_M0          	10     
#define BOARD_PWM_M1          	9
#define BOARD_PWM_M2          	29
#define BOARD_PWM_M3          	30
//

/* Total number of GPIO pins that are broken out to headers and
 * intended for general use. */
#define BOARD_NR_GPIO_PINS      31//26//44

/* Number of USARTs/UARTs whose pins are broken out to headers */
//#define BOARD_NR_USARTS         3

/* Default USART pin numbers (not considering AFIO remap) */
#define BOARD_USART1_TX_PIN     11  //D9  (PA9)
#define BOARD_USART1_RX_PIN     12	//D10 (PA10)
#define BOARD_USART2_TX_PIN     4	//D2  (PA2)
#define BOARD_USART2_RX_PIN     5	//D3  (PA3)
#define BOARD_USART3_TX_PIN     24	//D24 (PB10)
#define BOARD_USART3_RX_PIN     25	//D25 (PB11)

/* Number of SPI ports */
//#define BOARD_NR_SPI            2

/* Default SPI pin numbers (not considering AFIO remap) */
#define BOARD_SPI1_NSS_PIN      0 //D10 (PA4)
#define BOARD_SPI1_MOSI_PIN     7 //D11 PA7
#define BOARD_SPI1_MISO_PIN     6 //D12 PA6
#define BOARD_SPI1_SCK_PIN      1 //D13 PA5
#define BOARD_SPI2_NSS_PIN      18 //D26 PB12
#define BOARD_SPI2_MOSI_PIN     21 //D29 PB15
#define BOARD_SPI2_MISO_PIN     20 //D28 PB14
#define BOARD_SPI2_SCK_PIN      19 //D27 PB13

void boardInit(void);

/*[SteamMaker] CupDrone External Pin 1~5 
   2015.11.07 */

#define BOARD_Extern_PIN1   18  // GPIO PB18/ADC
#define BOARD_Extern_PIN2   19  // GPIO PB19/ADC
#define BOARD_Extern_PIN3   20  // GPIO PB20/ADC
#define BOARD_Extern_PIN4   21  // GPIO PB21/ADC
#define BOARD_Extern_PIN5   1   // GPIO PA5

#endif 
