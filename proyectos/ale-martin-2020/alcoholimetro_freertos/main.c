#include "FreeRTOS.h"
#include "task.h"
#include <util/delay.h>
#include "nokia_1100_lcd.h"
#include "adc.h"

double alcohol_en_sangre;
int promedio_adc;

double convertir_a_mg(int salida) {
	float voltaje, Rs;
	double alcohol;
	
	voltaje = salida * (5.0 / 1023.0); /*Convertimos la lectura en un valor de voltaje*/
	Rs = 1000 * ( (5 - voltaje) / voltaje);  /*Calculamos Rs con un RL de 1k*/
	alcohol = 0.4091 * pow( Rs / 5463 , -1.497); /*Calculamos la concentración  de alcohol con la ecuación obtenida.*/
	return alcohol;
}


static void vPantalla(void* pvParameters);
static void vSensor(void* pvParameters);


int main(void) {

	lcd_init();
	adc_init();
	
	/* Create task. Tarea pantalla */
    xTaskHandle pantalla_handle;
 
    xTaskCreate
    (
        vPantalla,
        (const char *)"pantalla",
        configMINIMAL_STACK_SIZE,
        NULL,
        tskIDLE_PRIORITY,
        &pantalla_handle
    );
    
    /* Create task. */
    xTaskHandle sensor_handle;
 
    xTaskCreate
    (
        vSensor,
        (const char *)"Sensor",
        configMINIMAL_STACK_SIZE,
        &pantalla_handle,
        tskIDLE_PRIORITY,
        &sensor_handle
    );

    /* Start scheduler. */
    vTaskStartScheduler();

	return 0;
}

static void vPantalla(void* pvParameters)
{
	vTaskDelay(500);
	for ( ;; )
	{
		alcohol_en_sangre = convertir_a_mg(promedio_adc);

		lcd_goto_xy(10,1);
		lcd_print_string("CONCENTRACION");
		lcd_goto_xy(10,2);
		lcd_print_string("   ALCOHOL ");
		lcd_goto_xy(4,4);
		lcd_print_string("|-------------|");
		lcd_goto_xy(4,5);
		lcd_print_string("| mg/L : ");	
		lcd_print_double(alcohol_en_sangre);
		lcd_print_string(" |");	
		lcd_goto_xy(4,6);
		lcd_print_string("|-------------|");
	}
}

static void vSensor(void* pvParameters)
{
	xTaskHandle pantalla_handle = *(xTaskHandle *)pvParameters;

    //uint16_t adc_result0;
    int suma_adc;
	int i = 0;
	vTaskDelay(500);

    for ( ;; )
	{
		suma_adc = 0;
		for (i = 0; i < 30; i++)
		{
			suma_adc = adc_single_read(0) + suma_adc;
		}
		promedio_adc = suma_adc / 30;

		vTaskDelay(1000);
		vTaskSuspend(pantalla_handle);
		vTaskDelay(100);
		vTaskResume(pantalla_handle);
	}
}

