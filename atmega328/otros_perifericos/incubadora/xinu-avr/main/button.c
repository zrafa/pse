/*
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los
 * pines 8-13 de arduino
 */

#define prende (0x38)
#define bit2 (0x04)
#define led (0x20)
#define foco (0x10)

/* puertos de E/S */
volatile unsigned char * puerto_b = (unsigned char *) 0x25; /* direccion de PORTB: SALIDA */
volatile unsigned char * ddr_b = (unsigned char *) 0x24; /* direccion de DDR B (registro de control) */
volatile unsigned char * pin_b = (unsigned char *) 0x23; /* direccion PIN B (registro de datos)*/
volatile unsigned char estado=0;


void port_b_init() {
        *(puerto_b) = *(puerto_b) & (~ prende);
        *(ddr_b) = *(ddr_b) | (prende);
        *(pin_b) =  0x04;
}


int button_get() {
	volatile unsigned char valor_b = *(pin_b);

        // valor_b &=  bit2 ;
        if (valor_b && bit2)
		return 0;
	
	return 1;
}


void prender_led() {

        volatile unsigned char valor_b = *(puerto_b);

        //valor_b |=  prende ;
        valor_b |=  led;
        *(puerto_b) = valor_b;
}

void apagar_led() {

        volatile unsigned char valor_b = *(puerto_b);

        //valor_b &= ~(prende);
        valor_b &= ~(led);
        *(puerto_b) = valor_b;
}

void titilar_cinco() {
	int i;

	for (i=0; i<5; i++) {
		prender_led();
		sleepms(250);
		apagar_led();
		sleepms(250);
	}
}

void apagar_foco() {

        volatile unsigned char valor_b = *(puerto_b);

       	valor_b |=  foco;

        *(puerto_b) = valor_b;
}

void prender_foco() {

        volatile unsigned char valor_b = *(puerto_b);

	valor_b &= ~(foco);

        *(puerto_b) = valor_b;
}

