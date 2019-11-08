CC=gcc
FLAGS=-Wall -g 
LIBS=-ltermbox
OUT=main
INCLUDE=-I headers/
OBJS=./out/main.o ./out/matrix.o

$(OUT): $(OBJS) ./out
	$(CC) $(FLAGS) $(LIBS) $(INCLUDE) -o $(OUT) $(OBJS) 

./out:
	mkdir ./out

./out/main.o: main.c headers/main.h headers/vector.h
	$(CC) $(FLAGS) $(INCLUDE) -o ./out/main.o -c main.c 

./out/matrix.o: matrix.c headers/matrix.h 
	$(CC) $(FLAGS) $(INCLUDE) -o ./out/matrix.o -c matrix.c 

.Phony: run

run:
	./$(OUT)

clean:
	rm $(OUT) out/*
