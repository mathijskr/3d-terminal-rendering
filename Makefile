CC=gcc
FLAGS=-Wall -g 
LIBS=-ltermbox
OUT=simulate
INCLUDE=-I headers/
OBJS=./out/main.o

$(OUT): $(OBJS) ./out
	$(CC) $(FLAGS) $(LIBS) $(INCLUDE) -o $(OUT) $(OBJS) 

./out:
	mkdir ./out

./out/main.o: main.c headers/main.h 
	$(CC) $(FLAGS) $(INCLUDE) -o ./out/main.o -c main.c 

.Phony: run

run:
	./$(OUT)

clean:
	rm $(OUT) out/*
