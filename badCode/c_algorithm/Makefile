V := @

Source := bfs.cpp
Runable := $(basename $(Source))
BIN := ./bin/

CC := g++ -std=c++14
GCC := $(CC) -W -Wall -O3 $(Source) -o $(BIN)$(Runable)
GDB-CC := $(CC) -g -W -Wall $(Source) -o $(BIN)$(Runable)
GDB := gdb -q $(BIN)$(Runable)

run: build
	$(V)$(BIN)$(Runable)

build: $(Source) mkdir
	$(V)$(GCC)

gdb: $(Source) mkdir
	$(V)$(GDB-CC)
	$(V)$(GDB)

mkdir:
	$(V)mkdir -p $(BIN)

clean:
	$(V)rm -rf $(BIN)

help:
	$(V)echo "run: run a executable."
	$(V)echo "build: build a executable."
	$(V)echo "gdb: for debugging."
	$(V)echo "clean: To remove some not important executable."
