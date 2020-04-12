
// Originalmente del ejemplo para Pi : gcc ssd1306.c -lwiringPi -o ssd1306

#include <avr/io.h>
#include <string.h>
// #include <string.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "twi.h"

#define WIDTH 128
#define HEIGHT 64

unsigned char buffer[ WIDTH * HEIGHT / 8 ];
// unsigned char i2cd;


unsigned char buf[2];
unsigned char addr;


void ssd1306_command(unsigned char c)
{
    // RAFA unsigned unsigned char control = 0x00;
    // RAFA wiringPiI2CWriteReg8( i2cd, control, c );
	buf[0] = 0x80;
	buf[1] = c;
	twi_write(addr, &buf[0], 2, NULL);
}

void ssd1306_byte(unsigned char c)
{
    // RAFA unsigned unsigned char control = 0x40;
    // RAFA wiringPiI2CWriteReg8( i2cd, control, c );
	buf[0] = 0x40;
	buf[1] = c;
	twi_write(addr, &buf[0], 2, NULL);
}

void ssd1306_render_buffer(void)
{
    ssd1306_command(0x21);          // column address
    ssd1306_command(0);             // Column start address (0 = reset)
    ssd1306_command(127);           // Column end address (127 
    ssd1306_command(0x22);          // page address
    ssd1306_command(0x00);          // Page start address (0 = reset)
    ssd1306_command(7);             // Page end address

    int i;

    for (i = 0; i < ( 128 * 64 / 8 ); i++) 
    {
        ssd1306_byte( buffer[i] ); 
    }
}

void ssd1306_draw_pixel( unsigned char x, unsigned char y, unsigned char color )
{
    switch (color) 
    {
        case 1: // white
            buffer[x + ( y / 8 ) * WIDTH ] = 1;

            break;
        case 0: // black
            buffer[x + ( y / 8 ) * WIDTH ] = 0;
            break;
    }

}

void ssd1306_init()
{
    // RAFA i2cd = wiringPiI2CSetup( 0x3C ); // address
    addr = 0x3C;

    ssd1306_command(0xAE);          // 0xAE // display off
    ssd1306_command(0xD5);          // 0xD5 // set display clock division
    ssd1306_command(0x80);          // the suggested ratio 0x80
    ssd1306_command(0xA8);          // 0xA8 set multiplex
    ssd1306_command(63);            // set height
    ssd1306_command(0xD3);          // set display offset
    ssd1306_command(0x0);           // no offset
    ssd1306_command(64);            // line #0 setstartline
    ssd1306_command(0x8D);          // 0x8D // chargepump
    ssd1306_command(0x14);
    ssd1306_command(0x20);          // memory mode
    ssd1306_command(0x00);          // 0x0 act like ks0108
    ssd1306_command(161);           // segremap
    ssd1306_command(0xC8);          // comscandec
    ssd1306_command(0xDA);          // 0xDA set com pins
    ssd1306_command(0x12);
    ssd1306_command(0x81);          // 0x81 // set contract
    ssd1306_command(0xCF);
    ssd1306_command(0xD9);          // 0xd9 set pre-charge
    ssd1306_command(0xF1);
    ssd1306_command(0xDB);          // SSD1306_SETVCOMDETECT
    ssd1306_command(0x40);
    ssd1306_command(0xA4);          // 0xA4 // display all on resume
    ssd1306_command(0xA6);          // 0xA6 // normal display
    ssd1306_command(0x2E);          // deactivate scroll
    ssd1306_command(0xAF);          // --turn on oled panel
}

void ssd1306_clear_buffer(void)
{
    memset( buffer, 0, ( 128 * 64 / 8 ) * sizeof( unsigned char ) );
}

void main() 
{
	twi_init();  // Initalize the TWI.
	sei();       // Enable interrupts.

    ssd1306_init();
    ssd1306_clear_buffer();
//     ssd1306_draw_pixel( 10, 10, 1 );
     ssd1306_draw_pixel( 20, 20, 1 );
    ssd1306_render_buffer();
	while (1) {
    ssd1306_clear_buffer();
    ssd1306_draw_pixel( 10, 10, 1 );
    ssd1306_draw_pixel( 20, 20, 1 );
    ssd1306_render_buffer();
    // 	ssd1306_draw_pixel( 20, 20, 1 );
	_delay_us(100);
	}
}
