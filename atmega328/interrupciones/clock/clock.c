
#include <avr/io.h>
#include <avr/interrupt.h>

int ticks;

void timer0_init( void )
{
    cli();          
    TCCR0B |= (1<<CS01) | (1<<CS00);   //clock select is divided by 64.
    TCCR0A |= (1<<WGM01);              //sets mode to CTC
    // OCR0A = 0x7C;                      //sets TOP to 124 so the timer will overflow every 1 ms.    
    OCR0A = 0xF9;                      //sets TOP to 124 so the timer will overflow every 1 ms.    
    TIMSK0 |= (1<<OCIE0A);              //Output Compare Match A Interrupt Enable
    sei();                             //enable global interrupts
}

ISR(TIMER0_COMPA_vect)
{
    cli();
    ticks ++;
    if (ticks==1000) {
    	PORTB ^= ( 1 << PORTB5 );   
	ticks=0;
    }
    sei();
}

main()
{
    	DDRB |= ( 1 << PORTB5 );   


	timer0_init();

	for (;;);

}
