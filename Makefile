all: grid file_manager main

grid: 
	g++ grid.cc -o grid.o -c -lraylib

file_manager: 
	g++ file_manager.cc -o file_manager.o -c -lraylib

main: grid.o file_manager.o
	g++ main.cc grid.o file_manager.o -o main -lraylib

clean:
	rm -f grid.o file_manager.o main