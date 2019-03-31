#include <avr/io.h>
#include <stdio.h>


/* Completar la estructura de datos para que se superponga a los registros
   del periferico de hardware del USART del atmega328, segun sugerido
   en el apunte */

typedef struct
{
    uint8_t status_control_a;    /* ucsr0a USART Control and Status A */

    uint8_t status_control_b; /* ucsr0b USART Control and Status B */
    uint8_t status_control_c; /* ucsr0c USART Control and Status C */
    uint8_t _reserved; /* espacio sin utilizar */
    uint8_t baud_rate_l; /* ubrr0l baud rate low */
    uint8_t baud_rate_h; /* ubrr0h baud rate high */

    uint8_t data_es;    /* udr0 i/o data */

} volatile uart_t;

/* puntero a la estructura de los registros del periferico */
volatile uart_t *puerto_serial = (uart_t *) (0xc0);

char cadena[100];


#define USART_BAUDRATE 115200
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)
#define INIT 0x06
#define EN_RX_TX 0x18
#define EN_TX 0x20
#define EN_RX 0x80


void serial_init() {

	/* Escribir una rutina de inicializacion */



	/* El manual del atmega328p tiene un ejemplo. Adecuarla a C y
           la estructura de datos */

	/* Configurar los registros High y Low con BAUD_PRESCALE */

	puerto_serial->baud_rate_h = (unsigned char) (BAUD_PRESCALE>>8);
	puerto_serial->baud_rate_l = (unsigned char) (BAUD_PRESCALE);
	/* Configurar un frame de 8bits, con un bit de paridad y bit de stop */
	puerto_serial->status_control_c = (unsigned char)(INIT);

	/* Activar la recepcion y transmicion */
	puerto_serial->status_control_b = (unsigned char)(EN_RX_TX);

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

	while(!((puerto_serial->status_control_a) & (EN_TX)));


    /* Send the character via the serial port. */
    /* (escribir el dato al registro de datos de E/S */

	puerto_serial->data_es = outputChar;
}


unsigned char serial_get_char(void)
{
    /* Wait for the next character to arrive. */
    /* Completar con E/S programada similar a serial_put_char pero
       utilizando el bit correcto */

    // while ( /* completar con E/S programada */ )
    //     ;
	while(!((puerto_serial->status_control_a) & (EN_RX)));
    // return /* DEBE devolver el valor que se encuentra en el registro de datos de E/S */
	return (puerto_serial->data_es);

}

void serial_put_str (char * mensaje)
{
	int i = 0;
	while (mensaje[i] != '\0') {
		serial_put_char(mensaje[i]);
		i++;
	};
}

char* serial_get_str(void)
{
	int i = 0;
	char l = serial_get_char();
    while((l != '\r') && (l != '\n') && (l != '\0')){
		cadena[i]=l;
		i++;
		l = serial_get_char();
	};
	cadena[i]='\0';/*agrega el fin de cadena*/
	return cadena;

}
