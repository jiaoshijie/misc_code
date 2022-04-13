V := @

ANOTHER :=
# THREAD := -lpthread

run: build
	$(V)./demo

build:
	$(V)g++ -std=c++17 -W -Wall -o demo syntax.cpp $(ANOTHER) -g $(THREAD)

gdb: build
	$(V)gdb demo -q

clean:
	$(V)rm -rf demo
	$(V)echo "removed demo"
