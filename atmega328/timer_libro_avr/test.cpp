#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

volatile int toggle;

int main(void)
{
	Timer timer;

    timer.start(500, Periodic);     // Start a periodic 500-ms timer.

    DDRC |=1<<PC2;  /* PC2 will now be the output pin */

	toggle = 0;

    OCR1A = 15624;

    TCCR1B |= (1 << WGM12);
    // Mode 4, CTC on OCR1A

    TIMSK |= (1 << OCIE1A);
    //Set interrupt on compare match

    TCCR1B |= (1 << CS12) | (1 << CS10);
    // set prescaler to 1024 and start the timer


    sei();
    // enable interrupts


    while (1);
    {
        // we have a working Timer
    }

	return 0;
}

ISR (TIMER1_COMPA_vect)
{
    // action to be done every 1 sec

	if (toggle == 0) {
    	PORTC &= ~(1<<PC2);/* PC2 LOW */
		toggle = 1;
	} else {
    	PORTC |=(1<<PC2); /* PC2 HIGH */
		toggle = 0;
	}

}

