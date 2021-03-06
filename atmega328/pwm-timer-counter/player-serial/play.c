/*
 * Ejemplo de PWM y timer con interrupciones
 *
 * Reproduce un wav de 11000 hz, 8bit, obtenido via uart a 115200
 * en la salida OC1A 
 */

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "serial.h"

volatile uint16_t sample;
int sample_count;

volatile unsigned char music[1500];

/* initialise the PWM */
void pwm_init(void)
{
    /* use OC1A pin as output */
    DDRB = _BV(PB1);

    /*
    * clear OC1A on compare match
    * set OC1A at BOTTOM, non-inverting mode
    * Fast PWM
    */
    TCCR1A = _BV(COM1A1) | _BV(WGM11);
   
    /*
    * Fast PWM, ICR1 (modo 14)
    * Prescaler: ninguno 
    * PWM frequency = 16Mhz / 1000(registro ICR1) = 16kHz
    */
    TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS10);
   
    /* set initial duty cycle to zero */
    OCR1A = 0;
    ICR1 = 1000;
    sample_count = 2;
   
    /* Queremos una interrupcion cada vez que llegue al TOP */
    TIMSK1|=(1<<TOIE1);


    sei(); /* Enable interrupts */
}


volatile unsigned int pcm_length;


ISR(TIMER1_OVF_vect)
{
	/* Cada dos interrupciones enviamos un nuevo valor (duty cycle)
 	 * Estamos haciendo 16000 interrupciones por segundo
	 */
	sample_count--;
	if (sample_count == 0) {   

		/* OCR1A = music[sample]; */
		OCR1A = serial_get_char();

/*
		sample++;
		if (sample > pcm_length) 	
			sample=0;
*/

		sample_count = 2;
	}
}



int main(void)
{
	int i;

	DDRB = 0xFF;
	PORTB &= ~(1 << PB5);

/* NO utilizo buffer por ahora */
	serial_init();
/*
	for (i=0; i<1400; i++)
		music[i] = serial_get_char();
	pcm_length = 1500;
   
*/
	pwm_init();

	PORTB |= (1 << PB5);
	while(1) {

/* NO utilizo buffer por ahora */
/*
		i++;
		if (i == 1500) i = 0;
		music[i] = serial_get_char();
*/
	};



}

