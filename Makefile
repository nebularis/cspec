
CC = gcc
LEG = leg

all: clean parser build
  
clean:
	rm -fr build
	rm -fr bin
  
build:
	mkdir build bin
	$(CC) -c src/cspec.c -std=c99 -o ./build/cspec.o
	$(CC) src/*.c -std=c99 -o ./bin/cspec

parser:
	$(LEG) src/parser.leg > src/parser.c
	
test: all
	./bin/cspec < spec/hook_spec.c  > spec/hook.c
	$(CC) ./build/cspec.o spec/hook.c -std=c99 -I src -o ./bin/test
	./bin/test