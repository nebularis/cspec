
CC = gcc
LEG = leg
BIN = bin/cspec
CFLAGS = -std=c99 -I src

all: clean parser build
  
clean:
	rm -fr build
	rm -fr bin
	rm src/parser.c
  
build: 
	mkdir build bin
	$(CC) -c src/cspec.c $(CFLAGS) -o ./build/cspec.o
	$(CC) src/*.c $(CFLAGS) -o $(BIN)

parser:
	$(LEG) src/parser.leg > src/parser.c
	
build_tests:
	$(CC) ./build/cspec.o spec/hook.c $(CFLAGS) -o ./bin/test
		
parse_tests:
	./$(BIN) < spec/hook_spec.c > spec/hook.c
		
test: all parse_tests build_tests
	./bin/test
	
install: $(BIN)
	install $(BIN) /usr/bin/cspec
	
