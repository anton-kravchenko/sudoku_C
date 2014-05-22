
#ifndef CONTAINER_H_
#define CONTAINER_H_
#define STEP_FOR_COL 3
#define STEP_FOR_RAW 1
#include "matrix.h"
#include "dimensions.h"

typedef struct{
	Matrix container[CONTAINER_SIZE];
	int all_empty_numbers;
} Container;

Container* fill_container(Container*, char**);
void show_buffer(char**);
void show_container(Container*);
void show_matrix(Container*, int);
int define_matrix_number(int,int);
Matrix* get_matrix(Container*,int);
int* get_line(char**, int n);
Item** get_items(Container*, int, int);
Item** get_col(Container *, int);
Item** get_raw(Container *, int);
int find_value_for(Container*, int, int);
void solve(Container*);

int* get_line(char** buffer, int n)
{
	int* numbers = (int*)malloc(sizeof(int)*RAW_SIZE);
	int i=0;

	char *line = buffer[n];
	while('\n' != *line)
	{
		if(('\n' != *line) & (' ' !=*line))
		{
			numbers[i] = *line - '0';
			i++;
		}
		line++;
	}
	return numbers;
}

Container* fill_container(Container* c, char **buffer)
{
	int i,j,matrix_number;

	Item **raw = (Item **)malloc(sizeof(Item));
	int* n = (int*)malloc(sizeof(int)* RAW_SIZE);

	for(i=0;i<9;i++)
	{
		n = get_line(buffer, i);
		raw = get_raw(c,i);

		for(j=0;j<9;j++)
		{
		raw[j]->number = n[j];
			if(0 == n[j])
			{
				matrix_number = define_matrix_number(i,j);
				c->container[matrix_number].empty_numbers++;
			}
		}
	}

	for(i=0;i<9;i++)
		c->all_empty_numbers+= c->container[i].empty_numbers;

	return c;
}

void show_buffer(char** buffer)
{
	int* n = (int*)malloc(sizeof(int)* RAW_SIZE);
	int k=0,i=0;

	for(;k<9;k++)
	{
	n = get_line(buffer, k);
		for(i=0;i<9;i++)
			printf("%d", n[i]);

	printf("\n");
	}
}

void show_container(Container* c)
{
	int i=0,j=0;
	Item **raw = (Item **)malloc(sizeof(Item));

	for(i=0;i<9;i++)
	{
	raw = get_raw(c, i);
		for(j=0;j<9;j++)
			printf("%d ", raw[j]->number);

	printf("\n");
	}

}

void show_matrix(Container* c, int n)
{

	Matrix* m = (Matrix*)malloc(sizeof(Matrix));
	m = get_matrix(c,n);

	int i=0;
	for(;i<9;i++)
		printf("%d ", m->matrix[i].number);

	printf("\n");
}

int define_matrix_number(int raw, int col)
{
	int n=0, min;
	min = (raw/3)*3;
	n = min + col/3;
	return n;

}

Matrix* get_matrix(Container* c,int n)
{

	Matrix *matrix = (Matrix*)malloc(sizeof(Matrix));
	matrix = &(c->container[n]);

	return matrix;
}

Item** get_items(Container* c, int n, int step)
{
		int matrix_number = 0;
		int el_number = 0;
		int temp = 0;

		if(STEP_FOR_RAW == step)
		{

			matrix_number = (n/3) * 3;
			el_number = (n%3) * 3;

		}else{

			matrix_number = n/3;
			el_number = n%3;

		}

		int i=0,j=0,k=0;
		temp = el_number;

		Item **cols = (Item**)malloc(sizeof(Item));

		for(i=0;i<9;i++)
			cols[i] = (Item*)malloc(sizeof(Item));

		for(i=0, k=0;i < 3; matrix_number+=step,i++)
			{

				for(j = 0, el_number = temp; j<3; el_number+=step, j++,k++)
					cols[k] = &(c->container[matrix_number].matrix[el_number]);

			}

		return cols;
}
Item** get_col(Container *c, int n)
{

	return get_items(c, n, STEP_FOR_COL);

}

Item**  get_raw(Container *c, int n)
{

	return get_items(c, n, STEP_FOR_RAW);

}

int find_value_for(Container* c, int raw, int col)
{
	int i=0, not_zero_variables=9;

	Item **line = (Item **)malloc(sizeof(Item));
	for(i=0;i<9;i++)
		line[i] = (Item*)malloc(sizeof(Item));

	line = get_raw(c, raw);

	Item **column = (Item **)malloc(sizeof(Item));
	for(i=0;i<9;i++)
		column[i] = (Item*)malloc(sizeof(Item));

	column = get_col(c, col);

	Matrix* matrix = (Matrix*)malloc(sizeof(Matrix));
	matrix = get_matrix(c, define_matrix_number(raw,col));

	int possible_numbers[] = {1,2,3,4,5,6,7,8,9};

	for(i=0;i<9;i++)
	{
		if(0 != line[i]->number)
		{
			if(-1 != possible_numbers[line[i]->number - 1])
			{
				not_zero_variables--;
				matrix->empty_numbers--;
				possible_numbers[line[i]->number - 1] = -1;
			}
		}
		if(0 != column[i]->number)
		{
			if(-1 != possible_numbers[column[i]->number - 1])
			{
				not_zero_variables--;
				matrix->empty_numbers--;
				possible_numbers[column[i]->number - 1] = -1;

			}
		}
		if(0 != matrix->matrix[i].number)
		{
			if(-1 != possible_numbers[matrix->matrix[i].number - 1])
			{
				not_zero_variables--;
				matrix->empty_numbers--;
				possible_numbers[matrix->matrix[i].number - 1] = -1;
			}
		}
	}

	if(1 == not_zero_variables)
	{

		for(i=0;i<9;i++)
		{
			if(-1 != possible_numbers[i])
			{
				c->all_empty_numbers--;
				return possible_numbers[i];
			}
		}
	}

return 0;
}

void solve(Container* c)
{
	int i=0,j=0;

	Matrix* m = (Matrix*)malloc(sizeof(Matrix));

	for(;i<9;i++)
	{
		m = get_matrix(c, i);
		for(j=0;j<9;j++)
		{
			if(0 == m->matrix[j].number)
			{
				m->matrix[j].number = find_value_for(c, ((i/3)*3+j/3), ((i%3)*3+j%3));
			}
		}
	}
}


#endif /* CONTAINER_H_ */
