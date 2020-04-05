// this code sets up counter0 for an 8kHz Fast PWM wave @ 16Mhz Clock


#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRD |= (1 << DDD3); //PD3 es OC2B. En arduino uno, el pin etiquetado con ~3
    DDRB |= (1 << DDB3); //PB3 es OC2A. En arduino uno, el pin etiquetado con ~11

    OCR2A = 0;
    OCR2B = 0;

    TCCR2A |= (1 << COM2A1);
    TCCR2A |= (1 << COM2B1);
    // set none-inverting mode

    TCCR2A |= (1 << WGM21) | (1 << WGM20);
    // set fast PWM Mode

    TCCR2B |= (1 << CS21);
    // set prescaler to 8 and starts PWM


    while (1)
    {
        OCR2A = 0; OCR2B = 255; _delay_ms(500);
        OCR2A = 128; OCR2B = 128; _delay_ms(500);
        OCR2A = 255; OCR2B = 0; _delay_ms(500);
        OCR2A = 128; OCR2B = 128; _delay_ms(500);
        
    }
}
