# IMPLEMENT ME

run: main
	./main

main: main.o functions.o classes.o
	g++ main.o -o main functions.o classes.o

main.o: main.cpp
	g++ -c main.cpp
