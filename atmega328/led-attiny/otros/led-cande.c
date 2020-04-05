
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
  unsigned char x;

  DDRB = DDRB | 0b00000001;


  while (1) {
    
      PORTB = 0b00000001; 
    _delay_ms(200);
      PORTB = 0b00000000; 
    _delay_ms(200);
  }
}
