Mini repo y documentacion de Como programar un attiny que esté virgen de fábrica
================================================================================

Este directorio contiene el código fuente de un programa baremetal para un 
attiny4313 utilizando avr-libc. Tambien su Makefile (para compilar y 
transferir el firmware, ya que son detalles bastantes difíciles de conseguir).

Por último se incluye el software de un programador icsp para avr en placas
arduinos.

Todo estos componentes en conjunto pueden ser utilizados para programar 
microcontroladoras Attiny de fábrica, que no contienen un bootloader 
ni otro software de ayuda.



 <figure>
  <img src="https://github.com/zrafa/pse/raw/master/atmega328/led-attiny/attiny.jpg" alt="Placa y foto de Candelaria." width="640">
  <figcaption>[Placa y foto de Candelaria.]</figcaption>
</figure> 

Como programar
--------------

Para programar micros avr de fábrica necesitamos utilizar la interfaz 
icsp (in-circuit system programming) de los micros avr.

Son 3 pasos (aunque el paso dos puede llevar mas pasos :)


1. Construimos una placa que contenga el attiny4313 con los pines expuestos 
del icsp (in-circuit system programming):

```
RESET
VCC
GND
CLK (SPI)
MISO (SPI)
MOSI (SPI)
```



2. Preparamos un programador. Podemos usar un arduino y seguir las 
instrucciones en el directorio avrisp/

3. Utilizamos el Makefile para compilar el programa en este directorio y 
utilizamos avrdude (luego del paso 2).





Otras consideraciones
---------------------


Para prepocesar y observar como el preprocesador del compilador traduce las macros 
de nombre de puertos a direcciones se puede ejecutar :

 avr-gcc -Os -DF_CPU=1000000UL -mmcu=attiny2313 -E led.c




Blog con varios posts de informacion de C unicamente para arduinos :

https://balau82.wordpress.com/2011/03/29/programming-arduino-uno-in-pure-c/


