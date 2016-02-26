


all: baremetalmr3020 

blink:
	cd blink-serial-a0040000 && cp main.c.blink main.c
	printf "\n	main.c generado para blink\n	Compilar con make all\n\n"

serial:
	cd blink-serial-a0040000 && cp main.c.serial main.c
	printf "\n	main.c generado para salida serial\n	Compilar con make all\n\n"

baremetalmr3020:
	cd blink-serial-a0040000 && make clean
	cd blink-serial-a0040000 && make
	cp blink-serial-a0040000/barebone.elf baremetalmr3020.elf
	mips-openwrt-linux-uclibc-objcopy -O binary -R .reginfo -R .notes -R .note -R .comment -R .mdebug -R .note.gnu.build-id -S baremetalmr3020.elf   baremetalmr3020.bin
	./mkfile.sh baremetalmr3020.bin
	./lzma e baremetalmr3020.bin -lc1 -lp2 -pb2 baremetalmr3020.bin.lzma
	dd if=/dev/zero of=root.jffs2-64k bs=1M count=1
	echo -ne '\xde\xad\xc0\xde' >> root.jffs2-64k
#	./mktplinkfw -H 0x00110101 -W 1 -F 4Mlzma -N OpenWrt -V r32741  -k ./baremetalmr3020.bin.lzma -r ./root.jffs2-64k -a 0x10000 -j -o baremetalmr3020.flash.bin
#	./mktplinkfw -E 0xa0040000 -L 0xa0040000 -H 0x30200001 -W 1 -F 4Mlzma -N OpenWrt -V r32741  -k ./baremetalmr3020.bin.lzma -r ./root.jffs2-64k -a 0x10000 -j -o baremetalmr3020.flash.bin

	./mktplinkfw -c -H 0x07200103 -W 1 -N TL-MR3030 -s -F 4Mlzma -k baremetalmr3020.bin.lzma -o baremetal.img

clean:
	rm -rf  baremetalmr3020.elf baremetalmr3020.bin baremetalmr3020.bin.lzma root.jffs2-64k baremetalmr3020.flash.bin 

