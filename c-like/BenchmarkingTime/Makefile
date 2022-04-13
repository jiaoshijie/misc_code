V := @

RunAndClean: run
	$(V)rm -rf demo

run: build
	$(V)./demo

build:
	$(V)c++ --std=c++14 -W -Wall -o demo test.cpp

clean:
	$(V)rm -rf demo
	$(V)echo "removed demo"
