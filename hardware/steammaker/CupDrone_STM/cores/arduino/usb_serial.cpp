/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung.
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

/**
 * @brief USB virtual serial terminal
 */

#include <string.h>


#include "wirish.h"
#include "usb.h"

#define USB_TIMEOUT 50


USBSerial::USBSerial(void) {
}

void USBSerial::begin(void) {
	/*
	 * [ROBOTIS][CHANGE] 2013-04-08 prevent to conflict other devices
	 * because setupUSB() is already initiated when board turn on.
	 * */
    //setupUSB();
}

void USBSerial::end(void) {
    disableUSB();
}

size_t USBSerial::write(uint8 ch) {
    const uint8 buf[] = {ch};
    this->write(buf, 1);

    return 0;
}

void USBSerial::write(const char *str) {
    this->write(str, strlen(str));
}

void USBSerial::write(const void *buf, uint32 len) {
    if (!(usbIsConnected() && usbIsConfigured()) || !buf) {
        return;
    }
//[ROBOTIS CHANGE][START]2012-12-14 fix some problems in transferring data to PC

    usbSendBytes((const uint8*)buf, len); // just call usbSendBytes()
  /*  uint32 txed = 0;
    uint32 old_txed = 0;
    uint32 start = millis();

    while (txed < len && (millis() - start < USB_TIMEOUT)) {
        txed += usbSendBytes((const uint8*)buf + txed, len - txed);
        if (old_txed != txed) {
            start = millis();
        }
        old_txed = txed;
    }*/
//[ROBOTIS CHANGE][END]2012-12-14 fix some problems in transferring data to PC

}

uint32 USBSerial::available(void) {
    return usbBytesAvailable();
}

uint32 USBSerial::read(void *buf, uint32 len) {
    if (!buf) {
        return 0;
    }

    uint32 rxed = 0;
    while (rxed < len) {
        rxed += usbReceiveBytes((uint8*)buf + rxed, len - rxed);
    }

    return rxed;
}

/* Blocks forever until 1 byte is received */
uint8 USBSerial::read(void) {
    uint8 buf[1];
    this->read(buf, 1);
    return buf[0];
}

uint8 USBSerial::pending(void) {
    return usbGetPending();
}

uint8 USBSerial::isConnected(void) {
    return usbIsConnected() && usbIsConfigured();
}

uint8 USBSerial::getDTR(void) {
    return usbGetDTR();
}

uint8 USBSerial::getRTS(void) {
    return usbGetRTS();
}

/**
 * [ROBOTIS][START]2012-12-14 add to support making user interrupt function
 *
 * @brief attach a USB Virtual COM interrupt.
 * @param function pointer indicating user defined interrupt.
 *
 * */
void USBSerial::attachInterrupt(voidFuncPtrUsb handler) {

	usb_attach_interrupt(handler);
}
/*
 * @brief detach a USB Virtual COM interrupt.
 * @param function pointer indicating user defined interrupt.
 * */
void USBSerial::detachInterrupt(void) {

	usb_detach_interrupt();
}
/*
 * [ROBOTIS][END]2012-12-14 add to support making user interrupt function
 */


USBSerial SerialUSB;
