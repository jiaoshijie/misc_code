V := @

Source := ./syntax.c ./other.c
LIB := -lX11
runAndClean: run clean
CFLAGS := -W -Wall -Wno-unused-parameter -Wno-unused-variable

run: build
	$(V)./demo

build:
	$(V)gcc $(CFLAGS) -o demo $(Source) $(LIB)

gdb:
	$(V)gcc $(CFLAGS) -o demo $(Source) -g $(LIB)
	$(V)./gdb -q ./demo
	$(V)rm -rf ./demo

clean:
	$(V)rm -rf ./demo
