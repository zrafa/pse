Programa de ejemplo de comunicación via un led.

Realiza una comunicacion wireless usando el led del teclado de una PC.
La recepción es a través de una fotoresistencia y un micro AVR.

El envío se realiza a través del programa send.c en el directorio PC/
El código en el raíz es la aplicación emebebida para el AVR.

Compilar con :

```
make clean
make 
make flash  # transfiere el firmware al AVR
```


El programa de envío en PC:

```
cd PC/
make send
```

Uso:

```
./send "frase a transmitir"
```


NOTAS: hay que calibrar el LED ON/OFF para la aplicación embebida
(esto es, la señal analógica obtenida puede ser de distinta intensidad
según la luz del ambiente. Calibrar usando el ADC del AVR para LED ON/OFF).


