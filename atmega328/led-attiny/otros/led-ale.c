
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
  unsigned char x;

  DDRB = DDRB | 0b00000001;
  PORTB = PORTB | 0b00000010;


  while (1) {
    x = PINB & 0b00000010; 

    if (x == 0)
        PORTB = PORTB | 0b00000001; 
    else
        PORTB = PORTB & 0b11111110; 
    _delay_ms(200);
  }
}
