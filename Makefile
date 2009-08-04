
CC = gcc
LEG = leg

all: clean parser build
  
clean:
	rm -fr build
  
build:
	mkdir build
	$(CC) src/*.c -std=c99 -o ./build/cspec

parser:
	$(LEG) src/parser.leg > src/parser.c
	
test: all
	./build/cspec < spec/hook_spec.c  > spec/hook.c
	$(CC) spec/hook.c -I src -o ./build/test
	./build/test