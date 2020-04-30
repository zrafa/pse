
/* Ejemplo de controlador LCD ssd1306 usando i2c
 * Rafael Ignacio Zurita <rafa@fi.uncoma.edu.ar>
 *
 */

#ifndef LCD_SSD1306_H
#define LCD_SSD1306_H

#define WIDTH 128
#define HEIGHT 64

void lcd_ssd1306_command(unsigned char c);
void lcd_ssd1306_byte(unsigned char c);
void lcd_ssd1306_render_buffer(void);
void lcd_ssd1306_render_column_buffer(int column, int page);

void lcd_ssd1306_draw_pixel( unsigned char x, unsigned char y, unsigned char color );
void lcd_ssd1306_draw_char(unsigned char x, unsigned char y, unsigned char c,
                            unsigned char color);
void lcd_ssd1306_init();
void lcd_ssd1306_clear_buffer(void);
void lcd_ssd1306_print_text(unsigned char x, unsigned char y, const char *text);

#endif  /* LCD_SSD1306_H */
