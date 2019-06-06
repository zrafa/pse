/******************************************************************************

timer 0 interrupt AVR atmega328p Microcontroller.

Crystal: 16MHz


*******************************************************************************/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile int ticks = 0;



void toggle_led() {
	PORTB ^= (1 << PB5);
}


void main()
{

   /* Configurar timer 0 */

   TCCR0A |= (1 << WGM01);
   OCR0A = 125;

   TIMSK0 |= (1 << OCF0A);
   /* | (1<< TOIE0); */

   TCCR0B |= (1 << CS02) | (1 << CS00);



   DDRB |= (1 << PB5);
   PORTB |= (1 << PB5);

   sei();

   while(1)
   {

	if (ticks>=125) {
		toggle_led();
		cli();
		ticks = 0;
		sei();
	}

   }
}


ISR(TIMER0_COMPA_vect) {
     ticks++;
}

