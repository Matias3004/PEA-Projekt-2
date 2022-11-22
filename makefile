CC = clang++
CFLAGS = -Wall -Wextra -Wpedantic -g -std=c++11

all: PEA-Projekt2

start: PEA-Projekt2
	./PEA-Projekt2

PEA-Projekt2: bin bin/main.o bin/Graph.o bin/TS.o bin/SA.o bin/MainMenu.o
	$(CC) $(CFLAGS) -o PEA-Projekt2 bin/main.o bin/Graph.o bin/TS.o bin/SA.o bin/MainMenu.o

bin:
	mkdir bin

bin/main.o: src/main.cpp
	$(CC) -c $(CFLAGS) -o bin/main.o src/main.cpp

bin/Graph.o: src/Graph.cpp inc/Graph.hh
	$(CC) -c $(CFLAGS) -o bin/Graph.o src/Graph.cpp

bin/TS.o: src/TS.cpp inc/TS.hh
	$(CC) -c $(CFLAGS) -o bin/TS.o src/TS.cpp

bin/SA.o: src/SA.cpp inc/SA.hh
	$(CC) -c $(CFLAGS) -o bin/SA.o src/SA.cpp

bin/MainMenu.o: src/MainMenu.cpp inc/MainMenu.hh
	$(CC) -c $(CFLAGS) -o bin/MainMenu.o src/MainMenu.cpp

clean:
	rm -rf *.o bin PEA-Projekt2