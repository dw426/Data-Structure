#include <stdio.h>
#include <stdlib.h>
#define FALSE 	0
#define TRUE 	1

#define ROWS 13
#define COLS 17
#define START_ROW 1	// 1	// 6   // 6
#define START_COL 1	// 1	// 9   // 1
#define EXIT_ROW 11
#define EXIT_COL 15

int mark[ROWS][COLS];

// int maze[ROWS][COLS] = {	
// 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
// 1,0,1,0,0,0,1,1,0,0,0,1,1,1,1,1,1,
// 1,1,0,0,0,1,1,0,1,1,1,0,0,1,1,1,1,
// 1,0,1,1,0,0,0,0,1,1,1,1,0,0,1,1,1,
// 1,1,1,0,1,1,1,1,0,1,1,0,1,1,0,0,1,
// 1,1,1,0,1,0,0,1,0,1,1,1,1,1,1,1,1,
// 1,0,0,1,1,0,1,1,1,0,1,0,0,1,0,1,1,
// 1,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,
// 1,0,0,1,1,0,1,1,0,1,1,1,1,1,0,1,1,
// 1,1,1,0,0,0,1,1,0,1,1,0,0,0,0,0,1,
// 1,0,0,1,1,1,1,1,0,0,0,1,1,1,1,0,1,
// 1,0,1,0,0,1,1,1,1,1,0,1,1,1,1,0,1,
// 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

int maze[ROWS][COLS] = {	
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,0,1,0,0,0,1,1,0,0,0,1,1,1,1,1,1,
1,1,0,0,0,1,1,0,1,1,1,0,0,1,1,1,1,
1,0,1,1,0,0,0,1,1,1,1,1,0,0,1,1,1,
1,1,1,0,1,1,1,1,0,1,1,0,1,1,0,0,1,
1,1,1,0,1,0,0,1,0,1,1,1,1,1,1,1,1,
1,0,0,1,1,0,1,1,1,0,1,0,0,1,0,1,1,
1,0,1,1,1,1,0,0,0,1,1,1,1,0,1,1,1,
1,0,0,1,1,0,1,1,0,1,1,1,0,0,0,1,1,
1,1,1,0,0,0,1,1,0,1,1,0,0,0,0,0,1,
1,0,0,1,1,1,1,1,0,0,0,1,1,0,1,1,1,
1,0,1,0,0,1,1,1,1,1,0,1,1,1,0,0,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

#define MAX_STACK_SIZE COLS*ROWS
#define MAX_QUEUE_SIZE COLS*ROWS

typedef struct elm {
	short int		row;
	short int		col;
	short int		dir;
} element;

typedef struct {
	short int		vert;
	short int		horiz;
} offsets;

element stack[MAX_STACK_SIZE];
offsets move[8] = {{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};
int top = -1;

void print_result(char title[], int found)
{
	int 	visit_cnt = 0;
	int 	goal_length = 0;
	int 	i, j;
	char 	result[ROWS][COLS];
	char	buf[256];
	
	for (i=0; i<ROWS; i++)
		for(j=0; j<COLS; j++)
		{
			result[i][j] = maze[i][j] == 1 ? '|' : ' ';
			if (mark[i][j])
			{
				visit_cnt++;
				result[i][j] = '*';
			}
		}
	if (found)
		for (i=0; i <= top; i++)
		{
			result[stack[i].row][stack[i].col] = 'o';
			goal_length++;
		}
	result[START_ROW][START_COL] = 'S';
	result[EXIT_ROW][EXIT_COL] = 'G';

	printf("%s\n", title);
	for (i=0; i<ROWS; i++)
	{
		for(j=0; j<COLS; j++)
		{
			if (result[i][j] == 'S')
				// printf("\x1b[33m%c\x1b[0m", result[i][j]);
				printf("%c", result[i][j]);
			else if (result[i][j] == 'G')
				// printf("\x1b[32m%c\x1b[0m", result[i][j]);
				printf("%c", result[i][j]);
			else
				printf("%c", result[i][j]);
		}
		printf("\n");
	}	

	printf("%s\n", title);
	printf("  No. of Visited Nodes : %d\n", visit_cnt+1);
	printf("  Length of Goal Path : %d\n\n", goal_length-1);
}

void add(int *top, element item)
{
			stack[++*top] = item;
}

element delete(int *top)
{
			return stack[(*top)--];
}

void mark_init()
{
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++)
			mark[i][j] = 0;
}

void path(void)		// DFS search using stack
{   
	int		i, row, col, next_row, next_col;
	int 	dir, found = FALSE;
   	element position;

	mark_init(); 	// mark배열 initialize
	
	position.row = START_ROW;  
	position.col = START_COL; 
	position.dir = 0; // North
   	mark[position.row][position.col] = 1;
	add(&top, position);

	while (top > -1 && !found) 
	{
      	position = delete(&top);
      	row = position.row;
		col = position.col;
      	dir = position.dir;
		while (dir < 8 && !found)
		{
         	next_row = row + move[dir].vert;     /* move in direction dir */
         	next_col = col + move[dir].horiz;
         	if (next_row == EXIT_ROW && next_col == EXIT_COL)
            	found = TRUE;
			else if (!maze[next_row][next_col] 
					 && !mark[next_row][next_col])
			{ 
            	mark[next_row][next_col] = 1;
           		position.row = row;
				position.col = col;
				position.dir = ++dir;  
            	add( &top, position);
            	row = next_row;
				col = next_col;
				dir = 0;
         	}
         	else
				++dir;
		}
	}

	if (found)    {
		position.row = row;		// 출구를 발견한 현재 위치
		position.col = col;
		position.dir = 0;
		add(&top, position);
		
		position.row = EXIT_ROW;	// 출구 위치 
		position.col = EXIT_COL; 
		position.dir = 0;
		add(&top, position);
   	}
   	else 
		printf("This maze has NO PATH to Goal!!\n");
	print_result("DFS : ", found);
}

void main()
{
	path();	// DFS
}
