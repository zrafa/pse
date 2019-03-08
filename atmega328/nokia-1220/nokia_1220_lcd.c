/* Nokia 1220 LCD test */

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/pgmspace.h>

// set output pins for lcd here
/*
#define sclk    PORTB.0
#define sda     PORTB.1
#define cs      PORTB.2
#define rst     PORTB.3
*/
/*
#define SCLK_SET     { PORTC |= (1<<PC3); //asm("NOP"); }
#define SDA_SET      { PORTC |= (1<<PC2); //asm("NOP"); }
#define CS_SET       { PORTC |= (1<<PC1); //asm("NOP"); }
#define RST_SET      { PORTC |= (1<<PC0); //asm("NOP"); }

#define SCLK_RESET    { PORTC &= ~(1<<PC3); //asm("NOP"); }
#define SDA_RESET     { PORTC &= ~(1<<PC2); //asm("NOP"); }
#define CS_RESET      { PORTC &= ~(1<<PC1); //asm("NOP"); }
#define RST_RESET     { PORTC &= ~(1<<PC0); //asm("NOP"); }
*/

/* Cableado RAFA */
//        PCF8814(unsigned char sclk  = 13,   /* clock       (display pin 2) */
//                unsigned char sdin  = 11,   /* data-in     (display pin 3) */
//                unsigned char reset = 12,   /* reset       (display pin 8) */
//                unsigned char sce   = 10);  /* enable      (display pin 5) */


/* RAFA pinout 1220
nokia pin


1 _RESET 	12
2 _CS		10
3 Vss		GND
4 DATA		11
5 CLOCK		13
6 Vlogic	3.3v
7 Vsupply	3.3v
8 VLCD (out)    capacitor 0.1uf a GND

*/


#define SCLK_SET     PORTB |= (1<<PB5)
#define SDA_SET      PORTB |= (1<<PB3)
#define CS_SET       PORTB |= (1<<PB2)
#define RST_SET      PORTB |= (1<<PB4)

#define SCLK_RESET    PORTB &= ~(1<<PB5)
#define SDA_RESET     PORTB &= ~(1<<PB3)
#define CS_RESET      PORTB &= ~(1<<PB2)
#define RST_RESET     PORTB &= ~(1<<PB4)

#define CMD     0
#define DATA    1

void Lcd_Clear(void);
void Lcd_Init(void);
void Lcd_Write(char cd,unsigned char c);
void SetX(char x);
void SetY(char y);
void Gotoxy(char x,char y);
void VLine(char x,char y,char on);
void Line(unsigned char x,unsigned char y,unsigned char y2,unsigned char on);
void print_char(char c);
//void print_message(char * message PROGMEM);
void print_string(char * message);

char bitaddr;
// lookup table, here you can modify the font
//const uint8_t backslash[] PROGMEM
const unsigned char FontLookup[96][5] PROGMEM ={
{0x00, 0x00, 0x00, 0x00, 0x00},// (space)
{0x00, 0x00, 0x5F, 0x00, 0x00},// !
{0x00, 0x07, 0x00, 0x07, 0x00},// "
{0x14, 0x7F, 0x14, 0x7F, 0x14},// #
{0x24, 0x2A, 0x7F, 0x2A, 0x12},// $
{0x23, 0x13, 0x08, 0x64, 0x62},// %
{0x36, 0x49, 0x55, 0x22, 0x50},// &
{0x00, 0x05, 0x03, 0x00, 0x00},// '
{0x00, 0x1C, 0x22, 0x41, 0x00},// (
{0x00, 0x41, 0x22, 0x1C, 0x00},// )
{0x08, 0x2A, 0x1C, 0x2A, 0x08},// *
{0x08, 0x08, 0x3E, 0x08, 0x08},// +
{0x00, 0x50, 0x30, 0x00, 0x00},// ,
{0x08, 0x08, 0x08, 0x08, 0x08},// -
{0x00, 0x30, 0x30, 0x00, 0x00},// .
{0x20, 0x10, 0x08, 0x04, 0x02},// /
{0x3E, 0x51, 0x49, 0x45, 0x3E},// 0
{0x00, 0x42, 0x7F, 0x40, 0x00},// 1
{0x42, 0x61, 0x51, 0x49, 0x46},// 2
{0x21, 0x41, 0x45, 0x4B, 0x31},// 3
{0x18, 0x14, 0x12, 0x7F, 0x10},// 4
{0x27, 0x45, 0x45, 0x45, 0x39},// 5
{0x3C, 0x4A, 0x49, 0x49, 0x30},// 6
{0x01, 0x71, 0x09, 0x05, 0x03},// 7
{0x36, 0x49, 0x49, 0x49, 0x36},// 8
{0x06, 0x49, 0x49, 0x29, 0x1E},// 9
{0x00, 0x36, 0x36, 0x00, 0x00},// :
{0x00, 0x56, 0x36, 0x00, 0x00},// ;
{0x00, 0x08, 0x14, 0x22, 0x41},// <
{0x14, 0x14, 0x14, 0x14, 0x14},// =
{0x41, 0x22, 0x14, 0x08, 0x00},// >
{0x02, 0x01, 0x51, 0x09, 0x06},// ?
{0x32, 0x49, 0x79, 0x41, 0x3E},// @
{0x7E, 0x11, 0x11, 0x11, 0x7E},// A
{0x7F, 0x49, 0x49, 0x49, 0x36},// B
{0x3E, 0x41, 0x41, 0x41, 0x22},// C
{0x7F, 0x41, 0x41, 0x22, 0x1C},// D
{0x7F, 0x49, 0x49, 0x49, 0x41},// E
{0x7F, 0x09, 0x09, 0x01, 0x01},// F
{0x3E, 0x41, 0x41, 0x51, 0x32},// G
{0x7F, 0x08, 0x08, 0x08, 0x7F},// H
{0x00, 0x41, 0x7F, 0x41, 0x00},// I
{0x20, 0x40, 0x41, 0x3F, 0x01},// J
{0x7F, 0x08, 0x14, 0x22, 0x41},// K
{0x7F, 0x40, 0x40, 0x40, 0x40},// L
{0x7F, 0x02, 0x04, 0x02, 0x7F},// M
{0x7F, 0x04, 0x08, 0x10, 0x7F},// N
{0x3E, 0x41, 0x41, 0x41, 0x3E},// O
{0x7F, 0x09, 0x09, 0x09, 0x06},// P
{0x3E, 0x41, 0x51, 0x21, 0x5E},// Q
{0x7F, 0x09, 0x19, 0x29, 0x46},// R
{0x46, 0x49, 0x49, 0x49, 0x31},// S
{0x01, 0x01, 0x7F, 0x01, 0x01},// T
{0x3F, 0x40, 0x40, 0x40, 0x3F},// U
{0x1F, 0x20, 0x40, 0x20, 0x1F},// V
{0x7F, 0x20, 0x18, 0x20, 0x7F},// W
{0x63, 0x14, 0x08, 0x14, 0x63},// X
{0x03, 0x04, 0x78, 0x04, 0x03},// Y
{0x61, 0x51, 0x49, 0x45, 0x43},// Z
{0x00, 0x00, 0x7F, 0x41, 0x41},// [
{0x02, 0x04, 0x08, 0x10, 0x20},// "\"
{0x41, 0x41, 0x7F, 0x00, 0x00},// ]
{0x04, 0x02, 0x01, 0x02, 0x04},// ^
{0x40, 0x40, 0x40, 0x40, 0x40},// _
{0x00, 0x01, 0x02, 0x04, 0x00},// `
{0x20, 0x54, 0x54, 0x54, 0x78},// a
{0x7F, 0x48, 0x44, 0x44, 0x38},// b
{0x38, 0x44, 0x44, 0x44, 0x20},// c
{0x38, 0x44, 0x44, 0x48, 0x7F},// d
{0x38, 0x54, 0x54, 0x54, 0x18},// e
{0x08, 0x7E, 0x09, 0x01, 0x02},// f
{0x08, 0x14, 0x54, 0x54, 0x3C},// g
{0x7F, 0x08, 0x04, 0x04, 0x78},// h
{0x00, 0x44, 0x7D, 0x40, 0x00},// i
{0x20, 0x40, 0x44, 0x3D, 0x00},// j
{0x00, 0x7F, 0x10, 0x28, 0x44},// k
{0x00, 0x41, 0x7F, 0x40, 0x00},// l
{0x7C, 0x04, 0x18, 0x04, 0x78},// m
{0x7C, 0x08, 0x04, 0x04, 0x78},// n
{0x38, 0x44, 0x44, 0x44, 0x38},// o
{0x7C, 0x14, 0x14, 0x14, 0x08},// p
{0x08, 0x14, 0x14, 0x18, 0x7C},// q
{0x7C, 0x08, 0x04, 0x04, 0x08},// r
{0x48, 0x54, 0x54, 0x54, 0x20},// s
{0x04, 0x3F, 0x44, 0x40, 0x20},// t
{0x3C, 0x40, 0x40, 0x20, 0x7C},// u
{0x1C, 0x20, 0x40, 0x20, 0x1C},// v
{0x3C, 0x40, 0x30, 0x40, 0x3C},// w
{0x44, 0x28, 0x10, 0x28, 0x44},// x
{0x0C, 0x50, 0x50, 0x50, 0x3C},// y
{0x44, 0x64, 0x54, 0x4C, 0x44},// z
{0x00, 0x08, 0x36, 0x41, 0x00},// {
{0x00, 0x00, 0x7F, 0x00, 0x00},// |
{0x00, 0x41, 0x36, 0x08, 0x00},// }
{0x08, 0x08, 0x2A, 0x1C, 0x08},// ->
{0x08, 0x1C, 0x2A, 0x08, 0x08} // <-
};

void main(void)
  {
  // MCUCSR = 0x80;
  // MCUCSR = 0x80;
  MCUCR = 0x80;
  MCUCR = 0x80;
  DDRB=0xFF;
  Lcd_Init();
  _delay_ms(100);
  Gotoxy(0,0);
  _delay_ms(100);
  print_string("RAFA RAFA !!  RAFA of Nokia     1100 LCD ..");
  _delay_ms(100);
  Gotoxy(20,5);
  _delay_ms(1000);
  print_string("It works!!");
  _delay_ms(1000);
 
  while(1)
  {
    print_string("FUNCIONA!!");
    _delay_ms(1000);
  }
  }

// clear LCD
void Lcd_Clear(void){
unsigned int i;
Lcd_Write(CMD,0x40); // Y = 0
Lcd_Write(CMD,0xb0);
Lcd_Write(CMD,0x10); // X = 0
Lcd_Write(CMD,0x00);
//Lcd_Write(CMD,0xae); // disable display;
for(i=0;i<864;i++)
Lcd_Write(DATA,0x00);
//Lcd_Write(CMD,0x07);
//Lcd_Write(CMD,0xaf); // enable display;
}







#define LCD_NOP 0xE3
#define LCD_MODE 0xA0
#define LCD_VOB_MSB 0x20
#define LCD_VOB_LSB 0x80
#define LCD_CHARGE_PUMP_ON 0x2F
#define LCD_RAM_ADDR_MODE 0xAA
#define LCD_CHANGE_ROW_LSB 0x00
#define LCD_CHANGE_ROW_MSB 0x10
#define LCD_CHANGE_COL 0xB0
#define LCD_MIRROR_Y 0xC0
#define LCD_MIRROR_X 0xA0
#define LCD_EXT_OSC 0x3A
#define LCD_SOFT_RESET 0xE2

#define LCD_CONTRAST 0x05

#define ON 0x01
#define OFF 0x00
#define ALL 0x04
#define INVERT 0x06
#define DISPLAY 0x0E


// init LCD
void Lcd_Init(void){
//RST_RESET;
CS_SET;
SCLK_RESET;

RST_RESET;
_delay_ms(1200);
RST_SET;

/* obtenido de pcf8511 de serdisplay.sf.net */

    Lcd_Write(CMD, 0xE1);               /* exit powersave */
    Lcd_Write(CMD, 0x2F);               /* hvgen on */
    Lcd_Write(CMD, 0x81);               /* set vop: */
    Lcd_Write(CMD, 0x3F);               /* vop */
    Lcd_Write(CMD, 0x20+5);             /* set voff */
    Lcd_Write(CMD, 0x64+3);             /* set mult fact */
    Lcd_Write(CMD, 0xA4);               /* no all pixels on mode */
    Lcd_Write(CMD, 0xAF);               /* display on */
    Lcd_Write(CMD, 0xAF);

/* ahora contraste y brillo */
      Lcd_Write(CMD, 0x45); /* NOP */
      Lcd_Write(CMD, 0x00); /* NOP */

      Lcd_Write(CMD, 0x81); /* set vop: */
      Lcd_Write(CMD, 0x3F); /* vop */
      Lcd_Write(CMD, 0x20 + 99); /*dd->curr_contrast*/



/*
Lcd_Write(CMD, 0x21);     
Lcd_Write(CMD, 0xC8);    
Lcd_Write(CMD, 0x06);    
Lcd_Write(CMD, 0x13);   
Lcd_Write(CMD, 0x20);  
Lcd_Write(CMD, 0x0c);     
_delay_us(500);
*/

/*

Lcd_Write(CMD,0b10100000); 
Lcd_Write(CMD,0b00000000); 
Lcd_Write(CMD,0b00010000); 
Lcd_Write(CMD,0b10110000); 
Lcd_Write(DATA,0b00000000); 


Lcd_Write(CMD,0xe2); 
Lcd_Write(CMD,0xa0); 
Lcd_Write(CMD,0xc0); 
Lcd_Write(CMD,0xa4); 
Lcd_Write(CMD,0x2f); 
Lcd_Write(CMD,0xaf); 

Lcd_Write(CMD, LCD_VOB_MSB|0x04);
Lcd_Write(CMD, LCD_VOB_LSB|(0x05 & 0x1F));

        Lcd_Write(CMD, LCD_MODE|DISPLAY|ON);
        Lcd_Write(CMD, LCD_MODE|ALL|OFF);
        Lcd_Write(CMD, LCD_MODE|INVERT|OFF);

*/
_delay_ms(200);            // 5mS so says the stop watch(less than 5ms will not work)


// Lcd_Clear();

// Lcd_Write(CMD,LCD_CHARGE_PUMP_ON); 


}


void Lcd_Write(char cd,unsigned char c)
{
    unsigned char i;
    CS_RESET;
   
    SCLK_RESET;
   
        if(cd)
            {
                SDA_SET;
            }
        else
            {
                SDA_RESET;
            }
       
    SCLK_SET;

        for(i=0;i<8;i++)
            {
            SCLK_RESET;
                if(c & 0x80)
                    {
                        SDA_SET;
                    }
                else
                    {
                        SDA_RESET;
                    }
            SCLK_SET;
            c <<= 1;
            _delay_ms(3);
            }
    CS_SET;
}


void SetX(char x){
    Lcd_Write(CMD,0x10 | ((x>>4)&0x7));
    Lcd_Write(CMD,x & 0x0f);
}

void SetY(char y){
    char aux = 0;
    while(y>7){
        y -=8;
        aux ++;
    }
  
    bitaddr = y-1;
    Lcd_Write(CMD,0xB0 | (aux & 0x0f));
}

void Gotoxy(char x,char y){
        Lcd_Write(CMD,(0xB0|(y&0x0F)));         // Y axis initialisation: 0100 yyyy          
        Lcd_Write(CMD,(0x00|(x&0x0F)));         // X axis initialisation: 0000 xxxx ( x3 x2 x1 x0)
        Lcd_Write(CMD,(0x10|((x>>4)&0x07))); // X axis initialisation: 0010 0xxx  ( x6 x5 x4)

}


//x dir >    y dir from last line to ^
void VLine(char x,char y,char on){
    char aux[8];
    char i;

    for(i=0;i<8;i++)
        aux[i] = 0;
      
    i = 7;
    while(y > 9){
        aux[i] = 0xff;
        y -= 8;
        i--;
    }
  
    while(y > 0){
        aux[i] >>= 1;
        aux[i] |= 0x80;
        y --;
    }  
  

  
    for(y=0;y<8;y++){
        Lcd_Write(CMD,0xB0 | y);
        SetX(x);      
        Lcd_Write(DATA,aux[y]);
    }  
      
}

// xdir is >       y is always < than y2  can be used for graphs
void Line(unsigned char x,unsigned char y,unsigned char y2,unsigned char on){
    char aux[8];
    char i,o=0;
    char c=1;
    char index;
  

  
    for(i=0;i<8;i++)
        aux[i] = 0;
      

    index = 0;
    for(i=0;i<64;i++){
      
        if(i >= y && i <= y2){
            aux[index] |= c << o;
        }
      
        o ++;
        if(o == 8){
            o = 0;
            index ++;
        }
    }
          
  
    for(i=0;i<8;i++){
        Lcd_Write(CMD,0xB0 | i);
        SetX(x);      
        Lcd_Write(DATA,aux[i]);
    }
  
  
}
    

      
void print_char(char c){
    int i;

            for ( i = 0; i < 5; i++ ){
                Lcd_Write(DATA,(pgm_read_byte(&FontLookup[c - 32][i]) << 1));  //pgm_read_byte(&backslash[i]);
        }
            Lcd_Write(DATA,0x00);

}

/*
void print_message(flash char * message){    // Write message to LCD (C string type)
Lcd_Write(CMD,0xae); // disable display;
        while (*message){            // Look for end of string
                    print_char(*message++);
                    }
    Lcd_Write(CMD,0xaf); // enable display;
                        }*/

void print_string(char * message){    // Write message to LCD (C string type)
//Lcd_Write(CMD,0xae); // disable display;
        while (*message){            // Look for end of string
                    print_char(*message++);
                    }
 //   Lcd_Write(CMD,0xaf); // enable display;
                        }

