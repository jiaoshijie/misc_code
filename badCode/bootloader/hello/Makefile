name = test10

all:
	@echo "ld: for a.out"
	@echo "as: for *.o"
	@echo "debug: for using gdb debug a.out"

as: $(name).s
	@gcc -m32 -c -g $(name).s -o $(name).o

ld: as
	@ld -m elf_i386 $(name).o

debug: ld
	@gdb -q a.out

clean:
	@rm -rf *.o a.out
