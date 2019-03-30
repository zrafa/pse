/*
  ATmega32 @ 8MHz
  Plays an 8bit/8000 sample PCM audio on OC1A output
*/

#include <stdint.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "pcm_sample.h"
#include <avr/interrupt.h>
#define SAMPLE_RATE 8000;

volatile uint16_t sample;
int sample_count;

/* initialise the PWM */
void pwm_init(void)
{
    /* use OC1A pin as output */
    DDRB = _BV(PB1);

    /*
    * clear OC1A on compare match
    * set OC1A at BOTTOM, non-inverting mode
    * Fast PWM, 8bit
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
   
    /* Queremos una interrupcion cada vez que llegue al TOP */
    TIMSK1|=(1<<TOIE1);

    sample_count = 2;

    sei(); /* Enable interrupts */
}



ISR(TIMER1_OVF_vect)
{
	/* Cada dos interrupciones enviamos un nuevo valor (duty cycle)
 	 * Esto permite hacer 8000 samples por segundo 8Mhz
	 */
	sample_count--;
	if (sample_count == 0) {   

		OCR1A = pgm_read_byte(&pcm_samples[sample]);

		sample++;
		if (sample > pcm_length) 	
			sample=0;

		sample_count = 2;
	}
}



int main(void)
{
   pwm_init();
   while(1);//do nothing
}

