/***************************************************************************
 *
 * Filename:	blink.c
 *
 * Description: The embedded systems equivalent of "Hello, World!"
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

#include "timer.h"
#include "led.h"
#include <avr/interrupt.h>


/**********************************************************************
 *
 * Function:    main()
 *
 * Description: Blink the green LED once a second.
 * 
 * Notes:       This outer loop is hardware-independent.  However, it
 *              calls the hardware-dependent function toggleLed().
 *
 * Returns:     This routine contains an infinite loop.
 *
 **********************************************************************/
int
main(void)
{
    Timer  timer;

    DDRC |= LED_GREEN;  /* PC2 will now be the output pin */
    DDRC |= LED_RED;  /* PC3 will now be the output pin */


//    timer.start(500, Periodic);     // Start a periodic 500-ms timer.
    timer.start(5, Periodic);     // Start a periodic 500-ms timer.

    while (1)
    {
        toggleLed(LED_RED);       // Toggle the green LED.

		// Do other useful work here.

        timer.waitfor();            // Wait for the timer to expire.
    }

	return 0;
}   /* main() */

ISR (TIMER1_COMPA_vect)
{
	PORTC ^= LED_GREEN;

	Timer::Interrupt();
}


