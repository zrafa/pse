
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
  DDRD = DDRD | 64;

  while (1) {
    PORTD = 0x00; _delay_ms(500);
    PORTD = 64; _delay_ms(500);
  }
}
