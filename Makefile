
CC = gcc
LEG = leg
CFLAGS = -std=c99 -I src

all: clean parser build
  
clean:
	rm -fr build
	rm -fr bin
	rm src/parser.c
  
build: 
	mkdir build bin
	$(CC) -c src/cspec.c $(CFLAGS) -o ./build/cspec.o
	$(CC) src/*.c $(CFLAGS) -o ./bin/cspec

parser:
	$(LEG) src/parser.leg > src/parser.c
	
build_tests:
	$(CC) ./build/cspec.o spec/hook.c $(CFLAGS) -o ./bin/test
		
parse_tests:
	./bin/cspec < spec/hook_spec.c > spec/hook.c
		
test: all parse_tests build_tests
	./bin/test
	
install: bin/cspec
	install bin/cspec /usr/bin/cspec
	
