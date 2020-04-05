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

#ifndef TIMER0_CONTADOR0_H
#define TIMER0_CONTADOR0_H

void timer0_contador0_init();

#endif /* TIMER0_CONTADOR0_H */
