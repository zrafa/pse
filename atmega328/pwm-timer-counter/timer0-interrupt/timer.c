/******************************************************************************

timer 0 interrupt AVR atmega328p Microcontroller.

Crystal: 16MHz


*******************************************************************************/
#include <avr/interrupt.h>

/* para contar la cantidad de interrupciones */
volatile int ticks = 0;

/* mascara para el led en el arduino pro mini */
#define LED_ROJO (0x20) /* 0b00100000 */

/* PUERTO B - led en la placa */
volatile unsigned char * puerto_b = (unsigned char *) 0x25;
volatile unsigned char * ddr_b = (unsigned char *) 0x24; /* direccion de DDR B */

typedef struct {
	unsigned char tccr0a;
	unsigned char tccr0b;
	unsigned char tcnt0;
	unsigned char ocr0a;
	unsigned char ocr0b;

} volatile contador0_t;

/* contador0: puntero a la estructura de los registros del periferico */
contador0_t * contador0 = (contador0_t *) (0x44);

/* reloj0: mascara de interrupciones */
volatile unsigned char * contador0_timsk0 = (unsigned char *) 0x6e;




void toggle_led() {
	*puerto_b = *puerto_b ^ (LED_ROJO);
}


void main()
{

   /* Configurar timer 0 modo CTC; WGM02=0, WGM01=1, WGM00=0, tope ocr0a */
   contador0->tccr0a |= 0b00000010;

   /* prescalar 1024 */
   contador0->tccr0b |= 0b00000101;

   /* 125 veces por segundo */
   contador0->ocr0a = 125;    /* 16Mhz/1024(prescalar)/125 = 125 veces/seg */

   /* TIMSK0: habilitamos interrupcion cuando el contador concuerde con ocr0a
    * OCIE0A=1
    */ 
   *contador0_timsk0 |= 0b00000010;

   /* habilitamos el led rojo */
   *ddr_b = *ddr_b | (LED_ROJO);
   *puerto_b = *puerto_b | (LED_ROJO);

   /* habilitamos las interrupciones */
   sei();

   while(1)
   {

	if (ticks>=125) {
		toggle_led();
		cli();
		ticks = 0;
		sei();
	}

   }
}


ISR(TIMER0_COMPA_vect) {
     ticks++;
}

