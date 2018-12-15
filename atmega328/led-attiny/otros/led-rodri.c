
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
  unsigned char x;

  DDRB = DDRB | 0b00000001;
  DDRD = DDRD | 0b00010000;

  PORTD = PORTD & 0b00000000;
  PORTD = PORTD | 0b00100000;

  while (1) {
    x = PIND & 0b00100000;
    
    if (x == 0)
      PORTB = 0b00000001; 
    else 
      PORTB = 0b00000000; 
    _delay_ms(200);
  }
}
