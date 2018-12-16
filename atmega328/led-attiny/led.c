
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
  DDRB = DDRB | 0b00000001;

  while (1) {
    PORTB = PORTB | 0b00000001; _delay_ms(500);
    PORTB = PORTB & 0b11111110; _delay_ms(500);
  }
}
