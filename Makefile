
CC = gcc
LEG = leg
BIN = bin/cspec
LIB = build/cspec.o
DEST = /usr/bin/cspec
CFLAGS = -std=c99 -I src
SPEC_BIN = bin/spec

all: clean $(BIN)
  
clean:
	rm -fr build
	rm -fr bin
	rm src/parser.c
  
$(BIN): src/parser.c 
	mkdir build bin
	$(CC) -c src/cspec.c $(CFLAGS) -o $(LIB)
	$(CC) src/*.c $(CFLAGS) -o $(BIN)

src/parser.c:
	$(LEG) src/parser.leg > src/parser.c
	
$(SPEC_BIN):
	$(CC) $(LIB) spec/hook.c $(CFLAGS) -o $(SPEC_BIN)
		
compile_specs:
	./$(BIN) < spec/hook_spec.c > spec/hook.c
		
test: all compile_specs $(SPEC_BIN)
	./$(SPEC_BIN)
	
install: $(BIN)
	install $(BIN) $(DEST)
	
.PHONY: install clean test compile_specs