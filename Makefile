all: grid main

grid: 
	g++ grid.cc -o grid.o -c -lraylib

main: grid.o
	g++ main.cc grid.o -o main -lraylib

clean:
	rm -f grid.o main