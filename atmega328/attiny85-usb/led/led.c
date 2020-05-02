#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
  DDRB = DDRB | 0b00111111;

  while (1) {
    PORTB = PORTB | 0b00111111; _delay_ms(1000);
    PORTB = PORTB & 0b11000000; _delay_ms(1000);
  }
}

