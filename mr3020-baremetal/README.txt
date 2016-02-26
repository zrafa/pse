
Programa baremetal minimo para ejecutar en un tplink mr3020
===========================================================

/*
 * Copyright (C) 2015 Facultad de Informática Universidad Nacional del Comahue.
 * Rodolfo del Castillo <rdc@fi.uncoma.edu.ar>
 * Rafael Ignacio Zurita <rafa@fi.uncoma.edu.ar>
 */

Enlaces iniciales del hello world para MIPS :

	http://linux.junsun.net/porting-howto/src/barebone/
	https://www.linux-mips.org/wiki/Linux/MIPS_Porting_Guide

El programa original hello world para MIPS de los enlaces fué adaptado para el mr3020.
Tambien existe un programa que realiza un blink.


Requisitos
----------

Toolchain de OpenWrt.


Ejemplo de Instrucciones de compilacion y ejecución
---------------------------------------------------
	
git clone https://github.com/zrafa/mr3020-baremetal.git
cd mr3020-baremetal

# Ajustar el archivo env.sh para que en PATH se encuentre su toolchain de openwrt uclibc
. env.sh      # O establezca en su variable PATH el directorio con los binarios uclibc de openwrt

make blink
make all

# Copiar baremetalmr3020.flash.bin al servidor tftp


# Como ejecutar : desde uboot en mr3020

tftpboot 0x80000000 baremetalmr3020.flash.bin
erase 0x9f020000 +0x3c0000
cp.b 0x80000000 0x9f020000 0x3c0000
bootm 9f020000

# El blink debería estar funcionando (tal vez lentamente)





Algunas consideraciones
-----------------------

make blink   
	General en el directorio blink-serial un main.c para generar un blink
	Luego se debe compilar todo con make all

make serial   
	General en el directorio blink-serial un main.c para generar realizar una salida serial 
	Luego se debe compilar todo con make all


make all
	Construye una imagen llamada baremetalmr3020.flash.bin, el cual es indicada para
	flashear. 
        uboot carga y ejecuta esta imagen en la dirección RAM SIN CACHE 0xa0040000


Ejemplo de compilacion y ejecucion desde RAM con uboot
------------------------------------------------------

make blink
make all
# Copiar baremetalmr3020.flash.bin al servidor tftp

# Desde uboot en mr3020
tftpboot 0x81000000 baremetalmr3020.flash.bin
bootm 81000000



Ejemplo compilacion y ejecucion desde FLASH con uboot
-----------------------------------------------------

make blink
make all
# Copiar baremetalmr3020.flash.bin al servidor tftp

# Desde uboot en mr3020
tftpboot 0x80000000 baremetalmr3020.flash.bin
erase 0x9f020000 +0x3c0000
cp.b 0x80000000 0x9f020000 0x3c0000
bootm 9f020000
