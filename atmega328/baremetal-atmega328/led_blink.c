
/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328 */

/* 
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los pines 8-13 de
 * arduino 
 */

/* mascara para el led en el arduino pro mini */
#define LED_ROJO (0x20) /* 0b00100000 */


void esperar() {

    volatile unsigned long i;

    /* delay manual */
    for (i=0; i<500000; i++);

}


int main(void)
{
    /* 
     * Paso 1 : Establecer el 5to bit del puerto B como salida
     * Poner en '1' el 5to bit de la dirección 0x24, que 
     * es el la dirección del registro "direccion de los datos" del puerto B
     * DDRB (Data Direction Register). El 5to bit estable como entrada o salida
     * el pin del atmega328p que tiene conectado un led en una board arduino
     */

    volatile unsigned char * puerto_b = (unsigned char *) 0x25;
    volatile unsigned char * ddr_b = (unsigned char *) 0x24; /* direccion de DDR B */

        *puerto_b = *puerto_b & (~LED_ROJO);
	*(ddr_b) = *(ddr_b) | (LED_ROJO);

    /*
     *
     * Paso 2:
     * Luego, para habilitar/deshabilitar (poner en ALTO/BAJO HIGH/LOW)
     * esa salida específica del puerto B
     * se debe poner en '1' el 5to bit de la dirección 0x25, que es la 
     * dirección del registro que controla el estado HIGH o LOW del 
     * pin de salida. En '1' ese bit enciende el led en una board arduino
     *
     * Poniendo en 0 la dirección anterior pone en LOW el pin de salida (apaga
     * el led)
     */

    while (1) {

        *puerto_b = *puerto_b | LED_ROJO;
	esperar();

        *puerto_b = *puerto_b & (~LED_ROJO);
	esperar();
    }

}
