
/* Genera 1000 interrupciones por segundo, utilizando el Timer0 de 8bits.
 *
 * 1 segundo 1000 milisegundos
 * 1 milisegundo 1000 microsegundos
 *
 * Utilizamos modo CTC, el cual compara con TOP. TOP es definido por OCR0A. 
 * Cuando CONTADOR == TOP el CONTADOR se pone a cero.
 *
 * reloj del sistema: 16000000 de ticks/s  /  64 (prescalar) = 250000 ticks/s
 *
 * 250000 ticks/s  /  250 = 1000 ticks/s => 
 */

#include <avr/io.h>
#include <avr/interrupt.h>

volatile int ticks = 0;

typedef struct
{
    uint8_t tccr0a; /* Registro de control A del timer0 */
    uint8_t tccr0b; /* Registro de control B del timer0 */
    uint8_t tcnt0;  /* Registro timer/contador */
    uint8_t ocr0a;  /* Registro comparador A */
    uint8_t ocr0b;  /* Registro comparador B */

} volatile timer0_t;

volatile timer0_t *timer0 = (timer0_t *)(0x44);

/* registro mascara de interrupciones timer 0 */
volatile unsigned char *timer0_timsk0 = (unsigned char *)(0x6E);

#define TIMER0_CS 0x03 /* prescalar=64 CS02|CS01|CS00 = 0b011 */
#define TIMER0_CTC 0x02 /* CTC = WGM = 0b010 : modo CTC es comparar y volver a cero*/

#define SYSTEM_TICKS 16000000
#define PRESCALAR 64
#define TICKS_PER_SECOND 1000

#define TIMER0_OCR0A (SYSTEM_TICKS/PRESCALAR/TICKS_PER_SECOND)


void timer0_init( void )
{
//    TCCR0B |= (1<<CS01) | (1<<CS00);   //clock select is divided by 64.
 //   TCCR0A |= (1<<WGM01);              //sets mode to CTC
  //  OCR0A = 0xF9;                      // Este valor tiene que ser 250 sets TOP to 124 so the timer will overflow every 1 ms.    
   // TIMSK0 |= (1<<OCIE0A);              //Output Compare Match A Interrupt Enable

	timer0->tccr0a |= TIMER0_CTC;
	timer0->tccr0b |= TIMER0_CS;
	timer0->ocr0a = TIMER0_OCR0A; /* valor contra el cual comparar */
	(*timer0_timsk0) |= 0x02;  /* 0x02: compara contra registro OCR0A y genera
				   interrupcion si hay un match */
}

extern char letra;
extern volatile int no_leer;

ISR(TIMER0_COMPA_vect)
{
    ticks ++;
    if (ticks > 100) {
    	PORTB ^= ( 1 << PORTB5 );   
	ticks=0;
	no_leer = 0;
   }
}


/*
main()
{
	cli();
    	DDRB |= ( 1 << PORTB5 );   


	timer0_init();
        sei();                             //enable global interrupts

	for (;;);

}
*/
