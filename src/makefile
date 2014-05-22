all: app
compiler = gcc
app: sudoku.c item matrix container dimensions
	$(compiler) -o sudoku sudoku.c item.h matrix.h container.h dimensions.h
item: item.h

matrix: item.h matrix.h

container: matrix

dimensions: dimensions.h
