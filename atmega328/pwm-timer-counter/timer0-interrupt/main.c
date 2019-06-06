/******************************************************************************
 *
 * Ejemplo de uso de un reloj/contador con interrupciones y seccion critica
 * Programacion de Sistemas Embebidos (materia electiva)
 *
 * Utilizamos el contador0 de 8bits
 * La implementación es en C como sigue:
 *  
 *   - Reloj/contador cero: con estructura y punteros en C
 *   - Puerto B (led rojo): con punteros en C
 *   - Rutina de atención de interrupciones: biblioteca de C AVR (GCC)
 *
 * AVR atmega328p Microcontroller
 * Crystal: 16MHz
 * 
 *****************************************************************************/

#include <avr/interrupt.h>
#include "timer0-contador0.h"

/* para contar la cantidad de interrupciones */
extern volatile int ticks;

/* mascara para el led en el arduino pro mini */
#define LED_ROJO (0x20) /* 0b00100000 */

/* PUERTO B - led en la placa */
volatile unsigned char * puerto_b = (unsigned char *) 0x25;
volatile unsigned char * ddr_b = (unsigned char *) 0x24; /* direccion de DDR B */


void toggle_led() {
	*puerto_b = *puerto_b ^ (LED_ROJO);
}


void main()
{

   timer0_contador0_init();

   /* habilitamos el led rojo */
   *ddr_b = *ddr_b | (LED_ROJO);
   *puerto_b = *puerto_b | (LED_ROJO);

   /* habilitamos las interrupciones */
   sei();

   while(1)
   {

	if (ticks>=125) {
		toggle_led();

		/* seccion critica */
		cli();	/* deshabilitamos las interrupciones */
		ticks = 0;
		sei();	/* habilitamos las interrupciones */
	}
   }
}
