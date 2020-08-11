Alcoholimetro digital implementado con FreeRTOS


Componentes:

-Arduino Pro Mini ATMega328
-Display LCD Nokia 1100
-Sensor de alcohol MQ-3 (Datasheet MQ-3)

El pin analógico del sensor MQ-3 se conecta a una entrada analógica del avr (A0), la alimentación del sensor es de 5V. Los pines de datos del display LCD se conectan a puertos de salida (GPIO) del avr mediante resistencias de 10K, la alimentación del display es de 3.3V. Ademas se conecta un interruptor al pin (1) del display para controlar la iluminación del mismo. Ver diagrama en el directorio imágenes.


Pasos para compilar y flashear:

$ git clone https://github.com/zrafa/pse.git
$ cd proyectos/ale-martin-2020/alcoholimetro_freertos
$ make
$ sudo make flash


Video demostración:

https://www.youtube.com/watch?v=eLc-GqMCyqg
