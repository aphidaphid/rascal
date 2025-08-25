CC=g++
FLAGS=-Wfatal-errors

SRC=main.cc
BIN=rascal

all: rascal

rascal:
	$(CC) $(FLAGS) $(SRC) -o $(BIN)

run: rascal
	./$(BIN)
