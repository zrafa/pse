/**********************************************************************
 *
 * Filename:    motor.h
 * 
 * API para la aplicacion embebida 
 *
 * META : ocultar el hardware a la aplicacion 
 *
 **********************************************************************/

void motor_init(void);
void avanzar_un_paso(void);
void retroceder_un_paso(void);
int get_posicion(void);
void ir_hasta_pos(int);
void avanzar_n_pasos(char);
void retroceder_n_pasos(char);

