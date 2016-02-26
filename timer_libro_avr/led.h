/**********************************************************************
 *
 * Filename:    led.h
 * 
 * Description: Header file for LED-related functionality.
 *
 * Notes:       The constants in this file are specific to Arcom's 
 *              Target188EB hardware.
 *
 * 
 * Copyright (c) 1998 by Michael Barr.  This software is placed into
 * the public domain and may be used for any purpose.  However, this
 * notice must not be changed or removed and no warranty is either
 * expressed or implied by its publication or distribution.
 **********************************************************************/

#ifndef _LED_H
#define _LED_H

#include <avr/io.h>

#define LED_RED   0x08      /* The red LED is controlled by bit 3.    */
#define LED_GREEN 0x04      /* The green LED is controlled by bit 2.  */

void toggleLed(unsigned char ledMask);


#endif /* _LED_H */

