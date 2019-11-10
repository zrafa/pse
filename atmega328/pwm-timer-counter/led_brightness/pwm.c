// this code sets up counter0 for an 8kHz Fast PWM wave @ 16Mhz Clock


#include <avr/io.h>
#include <util/delay.h>

void pwm_init()
{
    DDRD |= (1 << DDD6);
    // PD6 is now an output

    OCR0A = 0;
    // set PWM for 50% duty cycle


    TCCR0A |= (1 << COM0A1);
    // set none-inverting mode

    TCCR0A |= (1 << WGM01) | (1 << WGM00);
    // set fast PWM Mode

    TCCR0B |= (1 << CS01);
    // set prescaler to 8 and starts PWM
   
}

int main(void)
{
    pwm_init();

    while (1)
    {

        OCR0A = 0; _delay_ms(1500);
        OCR0A = 60; _delay_ms(1500);
        OCR0A = 128; _delay_ms(1500);
        OCR0A = 190; _delay_ms(1500);
        OCR0A = 255; _delay_ms(1500);
        
    }
}
