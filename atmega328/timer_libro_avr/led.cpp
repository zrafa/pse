/**********************************************************************
 *
 * Filename:    led.c
 * 
 * Description: LED-related functionality.
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

#include "led.h"

/**********************************************************************
 *
 * Function:    toggleLed()
 *
 * Description: Toggle the state of one or both LED's.
 *
 * Notes:       This function is specific to Arcom's Target188EB board.
 *
 * Returns:     None defined.
 *
 **********************************************************************/
void 
toggleLed(unsigned char ledMask)
{
	PORTC ^= ledMask;
}   /* toggleLed() */

