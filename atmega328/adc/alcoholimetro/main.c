#include <util/delay.h>

#include "nokia_1100_lcd.h"
#include "adc.h"


double convertir_a_mg(int salida) {
	float voltaje, Rs;
	double alcohol;
	
	voltaje = salida * (5.0 / 1023.0); /*Convertimos la lectura en un valor de voltaje*/
	Rs = 1000 * ( (5 - voltaje) / voltaje);  /*Calculamos Rs con un RL de 1k*/
	alcohol = 0.4091 * pow( Rs / 5463 , -1.497); /*Calculamos la concentración  de alcohol con la ecuación obtenida.*/
	return alcohol;
}

void mostrar_en_pantalla(double alcohol, int salida) {
	lcd_goto_xy(24,3);

	lcd_print_string("ADC:");
	lcd_print_int(salida, 3);

	lcd_goto_xy(24,4);
	
	lcd_print_string("mg/L:");	
	lcd_print_double(alcohol);

}

int main(void) {
	int salida;
	double alcohol_en_sangre;

	lcd_init();
	adc_init();

    while (1) {
        salida = adc_single_read(0);/*Leemos la salida analógica  del MQ*/
        alcohol_en_sangre = convertir_a_mg(salida);
        mostrar_en_pantalla(alcohol_en_sangre, salida);
        _delay_ms(500);
    }
    
}
