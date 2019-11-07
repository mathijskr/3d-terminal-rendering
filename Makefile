CC=gcc
FLAGS=-Wall -g 
LIBS=-ltermbox
OUT=main
INCLUDE=-I headers/
OBJS=./out/main.o ./out/cube.o ./out/vec_3d.o

$(OUT): $(OBJS) ./out
	$(CC) $(FLAGS) $(LIBS) $(INCLUDE) -o $(OUT) $(OBJS) 

./out:
	mkdir ./out

./out/main.o: main.c headers/main.h 
	$(CC) $(FLAGS) $(INCLUDE) -o ./out/main.o -c main.c 

./out/cube.o: cube.c headers/cube.h 
	$(CC) $(FLAGS) $(INCLUDE) -o ./out/cube.o -c cube.c 

./out/vec_3d.o: vec_3d.c headers/vec_3d.h 
	$(CC) $(FLAGS) $(INCLUDE) -o ./out/vec_3d.o -c vec_3d.c 

.Phony: run

run:
	./$(OUT)

clean:
	rm $(OUT) out/*
