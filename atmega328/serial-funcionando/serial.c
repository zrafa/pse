#include<avr/io.h>


/* Completar la estructura de datos para que se superponga a los registros
   del periferico de hardware del USART del atmega328, segun sugerido
   en el apunte */

typedef struct
{
	//Estos son los registros del HW USART asociados al perferico UART
    uint8_t status_control_a;    /* ucsr0a USART Control and Status A */

    /* demas registros */
	
	uint8_t status_control_b;   /* ucsr0b USART Control and Status B */
	uint8_t status_control_c;   /* ucsr0c USART Control and Status C */
	uint8_t _reserved;
	uint8_t baud_rate_l;        /* ubrr0l baud rate low */
	uint8_t baud_rate_h;        /* ubrr0h baud rate high */

    uint8_t data_es;    /* udr0 i/o data */

} volatile uart_t;

/* puntero a la estructura de los registros del periferico */
uart_t *puerto_serial = (uart_t *) (0xc0);



#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)


void serial_init() {

	/* Escribir una rutina de inicializacion */

	/* El manual del atmega328p tiene un ejemplo. Adecuarla a C y
           la estructura de datos */

	/* Configurar los registros High y Low con BAUD_PRESCALE */
	//establecemos la velocidad de transferencia de datos entre el 			   microprocesador y el periferico UART
	puerto_serial->baud_rate_h=(uint8_t) (BAUD_PRESCALE >> 8);

	puerto_serial->baud_rate_l=(uint8_t) BAUD_PRESCALE;

	/* Configurar un frame de 8bits, con un bit de paridad y bit de stop */
	//para configuar un frame de 8 bits debemos usar la combinacion 011, esto implica setear dos registros : status_control_c y status_control_b.
	puerto_serial->status_control_c=(uint8_t) (0x06);
	
	/* Activar la recepcion y transmicion */
	//me desplazo 2 bits a la izquierda y colocamos 111 en esa posicion
	puerto_serial->status_control_b=(uint8_t) (0x18);	

}


/* enviar un byte a traves del del dispositivo inicializado */
void serial_put_char (char outputChar)
{
    /* Wait until the transmitter is ready for the next character. */

    /* completar con E/S programada */
    /* Se debe esperar verificando el bit UDREn del registro UCSRnA,
       hasta que el buffer esté listo para recibir un dato a transmitir */

    // while ( /* completar con E/S programada */ )
    //     ;

	//usamos la mascara 0x20 porque debemos testear el estado del bit 5 del registro UCSRnA
	//me desplazo 5 bits a la izquierda o coloco en esa posicion un 1
	while(!((puerto_serial->status_control_a & (0x20))==0x20))
		;

    /* Send the character via the serial port. */
    /* (escribir el dato al registro de datos de E/S */
	puerto_serial->data_es=outputChar;
}


char serial_get_char(void)
{
    /* Wait for the next character to arrive. */
    /* Completar con E/S programada similar a serial_put_char pero 
       utilizando el bit correcto */
    
    // while ( /* completar con E/S programada */ )
    //     ;
	//RXC se enncuentra en la posicion 8.
	while(!((puerto_serial->status_control_a & (0x80))==0x80))
		;
    // return /* DEBE devolver el valor que se encuentra en el registro de datos de E/S */
	return puerto_serial->data_es;

}




