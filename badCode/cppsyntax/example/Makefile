V := @

Source := 14.cpp

run: build
	$(V)echo "****************************************"
	$(V)./demo

build: $(Source)
	$(V)g++ -std=c++14 -W -Wall -o demo $(Source)

gdb:
	$(V)g++ -std=c++14 -W -Wall -o demo $(Source) -g
	$(V)gdb demo -q

clean:
	$(V)rm -rf demo
