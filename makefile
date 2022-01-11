main: main.o functions.o classes.o
	$(ARGS) g++ main.o -o main functions.o classes.o

main.o: main.cpp
	$(ARGS) g++ -c main.cpp
