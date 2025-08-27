CC=g++
LIBS=-Ilib/glad/include -Isrc -lglfw
FLAGS=-Wfatal-errors

SRC=src/*.cc lib/glad/src/glad.c
BIN=rascal

all: rascal

clean:
	rm -rf ./$(BIN)

rascal: clean
	$(CC) $(FLAGS) $(LIBS) $(SRC) -o $(BIN)

run: rascal
	./$(BIN)
