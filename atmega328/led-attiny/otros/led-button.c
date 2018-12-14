
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
  unsigned char b;

  DDRB =  0b00001000;
  PORTB = 0b00011000;

	_delay_ms(5000);
  while (1) {
	b = PINB & 0b00010000;
	if (b == 0)
  		PORTB = PORTB | 0b00001000;
    	else 
  		PORTB = PORTB & 0b11110111;

	_delay_ms(500);
  }
}
