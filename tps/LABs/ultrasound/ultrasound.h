/*
 * ultrasound: controla el sensor HC-SR04 para medir distancias en cm
 */

/* ultrasound_get_distance()
 * 	devuelve la distancia en cm del objeto delante del sensor
 * 	devuelve -1 si no existe ningun objeto
 */
int ultrasound_get_distance(void);
