
/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328 */

/* 
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los pines 8-13 de
 *  arduino 
 */

#ifndef F_CPU
#define F_CPU 16000000UL // or whatever may be your frequency
#endif
 
#include <avr/io.h>
#include <util/delay.h>                // for _delay_ms()
 
int main(void)
{
    DDRB = 0x20;                       // initialize port B
    while(1)
    {
        // LED on
        PORTB = 0b00100000;            // PB5 = High = Vcc
        _delay_ms(1000);                // wait 1000 milliseconds (un segundo)
 
        //LED off
        PORTB = 0b00000000;            // PB5 = Low = 0v
        _delay_ms(1000);                // wait 1000 milliseconds (un segundo)
    }
}
