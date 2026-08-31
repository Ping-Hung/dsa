CC=gcc
FLAGS=-std=c2x -Wall -g -Werror -pedantic
SRC=main.c linked_list.c
EXE=linked_list

$(EXE): $(SRC)
	$(CC) $(SRC) $(FLAGS) -o $(EXE)

run: $(EXE)
	./$(EXE)

clean:
	rm $(EXE)

valgrind: $(EXE)
	valgrind -s --leak-check=full ./$(EXE)

.PHONY: run clean valgrind
