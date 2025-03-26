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

#include "timer_v01.h"
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
    Timer  timer1;
    Timer  timer2;

    DDRC |= LED_GREEN;  /* PC2 will now be the output pin */
    DDRC |= LED_RED;  /* PC3 will now be the output pin */


//    timer.start(500, Periodic);     // Start a periodic 500-ms timer.
    timer1.start(4, Periodic);     // Start a periodic 500-ms timer.
    timer2.start(2, Periodic);     // Start a periodic 500-ms timer.

    while (1)
    {
#if 0		
		timer2.waitfor();
      	toggleLed(LED_GREEN);       // Toggle the green GREEN.
#endif 
        if (timer1.isDone() == 1)
        	toggleLed(LED_GREEN);       // Toggle the green GREEN.
        if (timer2.isDone() == 1)
        	toggleLed(LED_RED);       // Toggle the green LED.		
    }

	return 0;
}   /* main() */

ISR (TIMER1_COMPA_vect)
{
	Timer::Interrupt();
}


