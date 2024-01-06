#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 16000000UL  // 1 MHz -- NOTE!! MUST SET TO MATCH AVR FUSES

void delay_seg(int n)
{
	volatile int i;

	for (i=0; i<n; i++)
		_delay_ms(1000);


}
int main(void)
{
	delay_seg(5);
	DDRB = DDRB | 0b00111111;

	PORTB = PORTB & 0b11000000;

	while (1) {
		PORTB = PORTB & 0b11000000;
		delay_seg(60*60*2);
		PORTB = PORTB | 0b00111111; 
		delay_seg(60*60*1);
	}
}

