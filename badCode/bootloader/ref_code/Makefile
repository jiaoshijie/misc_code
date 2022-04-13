all: bootloader

bootloader.o: bootloader.S
	as -o bootloader.o bootloader.S

bootloader: bootloader.o
	ld --oformat binary -N -e start -Ttext 0x00 -o bootloader bootloader.o
	# ld --oformat binary -N -e start -Ttext 0x7c00 -o bootloader bootloader.o

run: bootloader
	qemu-system-i386 -fda bootloader

debug: bootloader
	qemu-system-i386 -S -s -fda bootloader

clean:
	rm bootloader bootloader.o
