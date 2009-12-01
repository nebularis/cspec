
CC = gcc
LEG = leg
BIN = bin/cspec
LIB = build/cspec.o
DEST = /usr/bin/cspec
CFLAGS = -std=c99 -I src
SPEC_BIN = bin/spec

all: clean parser build
  
clean:
	rm -fr build
	rm -fr bin
	rm src/parser.c
  
build: 
	mkdir build bin
	$(CC) -c src/cspec.c $(CFLAGS) -o $(LIB)
	$(CC) src/*.c $(CFLAGS) -o $(BIN)

parser:
	$(LEG) src/parser.leg > src/parser.c
	
build_tests:
	$(CC) $(LIB) spec/hook.c $(CFLAGS) -o $(SPEC_BIN)
		
parse_tests:
	./$(BIN) < spec/hook_spec.c > spec/hook.c
		
test: all parse_tests build_tests
	./$(SPEC_BIN)
	
install: $(BIN)
	install $(BIN) $(DEST)
	
