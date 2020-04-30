
/* Ejemplo de controlador LCD ssd1306 usando i2c
 * Rafael Ignacio Zurita <rafa@fi.uncoma.edu.ar>
 *
 * El driver i2c está en : twi.c y twi.h (tiene interrupciones)
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

#include "lcd_ssd1306.h"
#include "twi.h"
#include "font.h"


void main() 
{
	/* variables para la animacion del pixel en pantalla */
	int i = 0;
	int inc_i = 0;
	int j = 0;
	int inc_j = 0;

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

	lcd_ssd1306_clear_buffer();
	lcd_ssd1306_draw_char(10, 3, 'P', 1);
	lcd_ssd1306_draw_char(16, 3, 'S', 1);
	lcd_ssd1306_draw_char(22, 3, 'E', 1);
	lcd_ssd1306_draw_char(28, 3, ' ', 1);
	lcd_ssd1306_draw_char(34, 3, '2', 1);
	lcd_ssd1306_draw_char(40, 3, '0', 1);
	lcd_ssd1306_draw_char(46, 3, '2', 1);
	lcd_ssd1306_draw_char(52, 3, '0', 1);
	lcd_ssd1306_render_buffer();
	_delay_ms(2000);

	/* animacion del pixel */
	inc_i = 1;
	inc_j = 1;
	while (1) {	/* Un programa embebido nunca finaliza */


		lcd_ssd1306_draw_pixel(i, j, 1);
		lcd_ssd1306_render_column_buffer(i , (j / 8));

		i = i + inc_i;
		if (i > 127) {
			i = 127;
			inc_i = -((rand() % 3) + 2);
		} else if (i < 0) {
			i = 0;
			inc_i = ((rand() % 3) + 2);
		}

		if ((i % 3) == 0) 	
			j = j + inc_j;

		if (j > 63) {
			j = 63;
			inc_j =-((rand() % 3) + 2);
		} else if (j < 0) {
			j = 0;
			inc_j =((rand() % 3) + 2);
		}

		_delay_us(100);
	}
}
