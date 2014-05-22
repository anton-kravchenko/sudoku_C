
#include <stdio.h>
#include <stdlib.h>
#include "item.h"
#include "container.h"
#include "matrix.h"


int main(void) {
	int i=0;
	Container *cc = malloc(sizeof(Container));
	char *buffer[9];
	for(i=0;i<9;i++)
		buffer[i] = malloc(9);

//	FILE *file  = fopen("sudoku.txt", "r");
	FILE *file  = fopen("sudoku_hard.txt", "r");
	for(i=0;i<9;i++)
	fgets(buffer[i], 14, file);

	fill_container(cc, buffer);

	printf("all empty numbers - %d\n", cc->all_empty_numbers);
	i=1;
	while(0 != cc->all_empty_numbers)
	{
		solve(cc);
		printf("iteration %d;empty-%d\n", i, cc->all_empty_numbers);
		i++;
	}

	show_container(cc);

	printf("item - %d, matrix - %d, container- %d",sizeof(Item), sizeof(Matrix), sizeof(Container));
	return EXIT_SUCCESS;
}
