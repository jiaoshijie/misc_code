V := @

Resource := test.cpp
CC := c++
RUNABLE := demo
ARGV := -std=c++14 -W -Wall -o $(RUNABLE)

runClean: run clean

run: build
	$(V)./$(RUNABLE)

build: $(Resource)
	$(V)$(CC) $(ARGV) $(Resource)

gdb:
	$(V)$(CC) $(ARGV) $(Resource) -g
	$(V)gdb $(RUNABLE) -q

clean:
	$(V)rm -rf $(RUNABLE)
