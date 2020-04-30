/* 
 * Controlador del LCD ssd1306 usando i2c
 * Rafael Ignacio Zurita <rafa@fi.uncoma.edu.ar>
 *
 * El driver i2c está en : twi.c y twi.h (con interrupciones)
 *
 * Pensado para usar en la materia Programacion de Sistemas Embebidos
 * Sacamos la idea y los comandos al LCD de un ejemplo original para 
 * RaspberryPi : gcc ssd1306.c -lwiringPi -o ssd1306 
 */

/* 
 * MEJORAS futuras:
 *
 * - Se pueden acelerar las escrituras de los los datos si 
 *   se envía una vez el byte de comando y luego el resto 
 *   de los bytes (en vez de un byte comando por cada
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

#include "twi.h"
#include "font.h"
#include "lcd_ssd1306.h"

unsigned char buffer[ WIDTH * HEIGHT / 8 ];
unsigned char addr;

void lcd_ssd1306_command(unsigned char c)
{
	unsigned char buf[2];

	buf[0] = 0x80;
	buf[1] = c;
	twi_write(addr, &buf[0], 2, NULL);
}

void lcd_ssd1306_byte(unsigned char c)
{
	unsigned char buf[2];

	buf[0] = 0x40;
	buf[1] = c;
	twi_write(addr, &buf[0], 2, NULL);
}

void lcd_ssd1306_render_buffer(void)
{
	int i;

	lcd_ssd1306_command(0x21);          // column address
	lcd_ssd1306_command(0);             // Column start address (0 = reset)
	lcd_ssd1306_command(127);           // Column end address (127 
	lcd_ssd1306_command(0x22);          // page address
	lcd_ssd1306_command(0x00);          // Page start address (0 = reset)
	lcd_ssd1306_command(7);             // Page end address

	for (i = 0; i < ( 128 * 64 / 8 ); i++) {
		lcd_ssd1306_byte( buffer[i] ); 
	}
}

void lcd_ssd1306_render_column_buffer(int column, int page)
{
	int i;

	lcd_ssd1306_command(0x21);          // column address
	lcd_ssd1306_command(column);        // Column start address (0 = reset)
	lcd_ssd1306_command(column);        // Column end address (127 
	lcd_ssd1306_command(0x22);          // page address
	lcd_ssd1306_command(page);          // Page start address (0 = reset)
	lcd_ssd1306_command(page);          // Page end address

	lcd_ssd1306_byte( buffer[page*128+column] ); 
}

void lcd_ssd1306_draw_pixel(unsigned char x, unsigned char y, unsigned char color)
{

	/* Las siguientes son posibles rotaciones de las columnas del display */
	/*
	 *	switch(getRotation()) {
	 *	case 1:
	 *	      ssd1306_swap(x, y);
	 *	      x = WIDTH - x - 1;
	 *	      break;
	 *	case 2:
	 *	      x = WIDTH  - x - 1;
	 *	      y = HEIGHT - y - 1;
	 *	      break;
	 *	case 3:
	 *	      ssd1306_swap(x, y);
	 *	      y = HEIGHT - y - 1;
	 *	      break;
	 *	}
	 */

	switch(color) {
	case 1:   
		buffer[x + (y/8) * WIDTH] |=  (1 << (y&7)); 
		break;
	case 0:   
		buffer[x + (y/8) * WIDTH] &= ~(1 << (y&7)); 
		break;
	}
}

void lcd_ssd1306_draw_char(unsigned char x, unsigned char y, unsigned char c,
                            unsigned char color)
{

	int i;
	int j;
	char line;

	/* El font de este codigo tiene letras de 5x8 bits */
	for (i = 0; i < 5; i++) { 	/* columnas */
		line = pgm_read_byte(&font[c * 5 + i]);

		for (j = 0; j < 8; j++) {  /* hileras */
			if (line & 1)
				lcd_ssd1306_draw_pixel(x + i, y + j, 1);
			else
				lcd_ssd1306_draw_pixel(x + i, y + j, 0);
			line = line >> 1;
		}
	}
}

void lcd_ssd1306_init()
{
	addr = 0x3C;	/* La direccion i2c del controlador del LCD */

	lcd_ssd1306_command(0xAE);          // 0xAE // display off
	lcd_ssd1306_command(0xD5);          // 0xD5 // set display clock division
	lcd_ssd1306_command(0x80);          // the suggested ratio 0x80
	lcd_ssd1306_command(0xA8);          // 0xA8 set multiplex
	lcd_ssd1306_command(63);            // set height
	lcd_ssd1306_command(0xD3);          // set display offset
	lcd_ssd1306_command(0x0);           // no offset
	lcd_ssd1306_command(64);            // line #0 setstartline
	lcd_ssd1306_command(0x8D);          // 0x8D // chargepump
	lcd_ssd1306_command(0x14);
	lcd_ssd1306_command(0x20);          // memory mode
	lcd_ssd1306_command(0x00);          // 0x0 act like ks0108
	lcd_ssd1306_command(161);           // segremap
	lcd_ssd1306_command(0xC8);          // comscandec
	lcd_ssd1306_command(0xDA);          // 0xDA set com pins
	lcd_ssd1306_command(0x12);
	lcd_ssd1306_command(0x81);          // 0x81 // set contract
	lcd_ssd1306_command(0xCF);
	lcd_ssd1306_command(0xD9);          // 0xd9 set pre-charge
	lcd_ssd1306_command(0xF1);
	lcd_ssd1306_command(0xDB);          // SSD1306_SETVCOMDETECT
	lcd_ssd1306_command(0x40);
	lcd_ssd1306_command(0xA4);          // 0xA4 // display all on resume
	lcd_ssd1306_command(0xA6);          // 0xA6 // normal display
	lcd_ssd1306_command(0x2E);          // deactivate scroll
	lcd_ssd1306_command(0xAF);          // --turn on oled panel
}

void lcd_ssd1306_clear_buffer(void)
{
	memset(buffer, 0, (WIDTH * HEIGHT / 8) * sizeof(unsigned char));
}

/* Muestra un texto en pantalla
 * x e y son coordenadas a resolución de pixel
 * Cada letra es de 6 columnas y 8 filas (1 columna es espacio)
 */
void lcd_ssd1306_print_text(unsigned char x, unsigned char y, const char *text)
{
	int i;
	char *c = text;

	while (*c) {
    		lcd_ssd1306_draw_char(x + (6 * i), y, (*c), 1);
		i++;
		c++;
	}
}
