
/* Ejemplo de controlador LCD ssd1306 usando i2c
 * Rafael Ignacio Zurita <rafa@fi.uncoma.edu.ar>
 *
 * El driver i2c está en : twi.c y twi.h (tiene interrupciones)
 * Driver i2c autor: https://github.com/scttnlsn/avr-twi
 *
 * Pensado para usar en la materia Programacion de Sistemas Embebidos
 * Sacamos la idea y los comandos al LCD de un ejemplo original para 
 * RaspberryPi : gcc ssd1306.c -lwiringPi -o ssd1306 
 */

/* POR HACER:
 *
 * - Se pueden acelerar las escrituras de los los datos si 
 *   se envía unicamente una sola vez el byte de comando
 *   y luego el resto de los bytes (en vez de un byte comando por cada
 *   byte de datos)
 *
 * - Se debe reescribir el driver i2c para usar solo baremetal
 *   sin las macros de avr-libc.
 */

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <string.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

#include "lcd_ssd1306.h"
#include "twi.h"
#include "font.h"
#include "usound.h"


void main() 
{
	/* variables para la animacion del pixel en pantalla */
	int i = 0;
	int inc_i = 0;
	int j = 0;
	int inc_j = 0;

	/* Inicializa el ultrasonido */
	usound_init();

	/* Inicializa el driver i2c / TWI */
	twi_init();

	/* Inicializa el driver del LCD ssd1306 */
	lcd_ssd1306_init();

	/* Enable interrupts. */
	sei();       

	/* Mostramos en pantalla un pixel y un texto */
	lcd_ssd1306_clear_buffer();
	lcd_ssd1306_draw_pixel( 1, 2, 1 );
	lcd_ssd1306_print_text(5,40, "Esperamos 2 seg.");
	lcd_ssd1306_render_buffer();
	_delay_ms(2000);


	uint32_t d = 0;
	uint32_t total = 0;
	uint32_t previo = 0;
	char m[30];
	sprintf(m, "distancia: %u cm ", d);
	m[29] = 0;
	lcd_ssd1306_print_text(5,5, m);
	lcd_ssd1306_render_buffer();
	_delay_ms(1000);

	while (1) {	/* Un programa embebido nunca finaliza */
		total = 0;

		lcd_ssd1306_clear_buffer();
		_delay_ms(5);
		d = readDistance();
		previo = d;
		total = d;

		for (i=0; i<5; i++) {
			_delay_ms(5);
			d = readDistance();
			if (abs((int)(d - previo)) < 100) {
				total = total + d;
				previo = d;
			} else {
				total = 0;
				break;
			}
				//total = total + d;
		}
	/*
		lcd_ssd1306_clear_buffer();
	sprintf(m, "distancia: %u cm ", total);
	m[29] = 0;
	lcd_ssd1306_print_text(5,5, m);
	lcd_ssd1306_render_buffer();
	continue;
*/
		total = total / 5;
		
		if (total > 390)
			sprintf(m, "distancia: nada che");
		else
			sprintf(m, "distancia: %u cm ", total);
		m[29] = 0;
		lcd_ssd1306_print_text(5,5, m);
		lcd_ssd1306_render_buffer();

		if (total != 0)
			_delay_ms(5000);
		else
			_delay_ms(500);


	}
}
