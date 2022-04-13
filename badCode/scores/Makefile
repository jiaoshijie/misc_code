V :=
# V := @

Source := main.cpp
Bin := demo
# HEAD := -I./head -I/usr/include/...
HEAD :=

CC := c++
CCARGV :=  -W -Wall
GDB := gdb -q -x ./tools/gdbinit

runAndclean: run clean

run: build
	$(V)./$(Bin)

build:
	$(V)$(CC) $(CCARGV) $(HEAD) -o $(Bin) $(Source)

dbuild:
	$(V)$(CC) $(CCARGV) $(HEAD) -o $(Bin) -g $(Source)

gdb: dbuild clean
	$(V)$(GDB) $(Bin)

externalCtags:
	$(V)$(CC) -M $(HEAD) $(Source) | sed -e 's/[\\ ]/\n/g' | sed -e '/^$$/d' -e '/\.o:[ \t]*$$/d' | ctags -L - --c++-kinds=+p --fields=+iaS --extras=+q -f .rtags

clean:
	$(V)rm -rf $(Bin)
