/******************************************************************************
 *
 * Driver timer0_contador0 (cero)
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

/* para contar la cantidad de interrupciones */
volatile int ticks = 0;

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


void timer0_contador0_init()
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

}


ISR(TIMER0_COMPA_vect) {
     ticks++;
}

