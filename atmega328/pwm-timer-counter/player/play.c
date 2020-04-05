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
    TCCR1A = _BV(COM1A1) | _BV(WGM10);
   
    /*
    * Fast PWM, 8bit
    * Prescaler: clk/1 = 8MHz
    * PWM frequency = 8MHz / (255 + 1) = 31.25kHz
    */
    TCCR1B = _BV(WGM12) | _BV(CS10);
    //TCCR1B = _BV(WGM12) | _BV(CS11);
   
    /* set initial duty cycle to zero */
    OCR1A = 0;
   
    /* Setup Timer0 */
    TCCR0B|=(1<<CS00);
    TCNT0=0;
    TIMSK0|=(1<<TOIE0);
    sample_count = 8;
    sei(); //Enable interrupts
}



ISR(TIMER0_OVF_vect)
{
    
         sample_count--;
         if (sample_count == 0)
            {
             sample_count = 8;          
             OCR1A = pgm_read_byte(&pcm_samples[sample++]);
             if(sample>pcm_length)sample=0;
            }
}



int main(void)
{
   pwm_init();
   while(1);//do nothing
}

