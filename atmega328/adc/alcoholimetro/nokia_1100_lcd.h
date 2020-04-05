#ifndef _NOKIA_1100_H
#define _NOKIA_1100_H

void lcd_init(void);
void lcd_print_string(char * message);
void lcd_print_int (int valor, int cant_digitos);
void lcd_print_double (double valor);
void lcd_clear(void);
void lcd_write(char cd,unsigned char c);
void lcd_set_x(char x);
void lcd_set_y(char y);
void lcd_goto_xy(char x,char y);
void lcd_v_line(char x,char y,char on);
void lcd_line(unsigned char x,unsigned char y,unsigned char y2,unsigned char on);

#endif /* _NOKIA_1100_H */

