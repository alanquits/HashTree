CC = gcc
FLAGS = -Wall
OBJECTS = example.o hashtree.o

example: $(OBJECTS)
	$(CC) $(OBJECTS) -o example

example.o: example.c
	$(CC) -c example.c $(FLAGS)

hashtree.o: hashtree.c hashtree.h
	$(CC) -c hashtree.c $(FLAGS)
