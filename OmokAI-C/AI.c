#include"AI.h"
#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

#define SIZE 19
#define BLACK 1
#define WHITE 2
#define NONE 0
#define random(n) (rand()%n)

//==============================================================================================================//

int value[SIZE][SIZE] = { NONE };		// 가치함수
extern int board[SIZE][SIZE];
extern int flag;

//==============================================================================================================//

void value_init()
{
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			value[i][j] = 0;

	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
		{
			if (board[i][j] != NONE)
				value[i][j] = -999;
		}
}

//==============================================================================================================//

void value_four()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE - 3; j++)
		{
			if (board[i][j] == board[i][j + 1] && board[i][j + 1] == board[i][j + 2] && board[i][j + 2] == board[i][j + 3] && board[i][j + 3] == WHITE)			// 가로로 연속해서 4개
			{
				if (j == 0)				value[i][j + 4] += 100;
				else if (j == SIZE - 4)	value[i][j - 1] += 100;
				else					value[i][j - 1] += 100, value[i][j + 4] += 100;
			}
			else if (board[i][j] == board[i][j + 1] && board[i][j + 1] == board[i][j + 2] && board[i][j + 2] == board[i][j + 3] && board[i][j + 3] == BLACK)	// 가로로 연속해서 4개
			{
				if (j == 0)				value[i][j + 4] += 95;
				else if (j == SIZE - 4)	value[i][j - 1] += 95;
				else					value[i][j - 1] += 95, value[i][j + 4] += 95;
			}
		}
	}

	for (int i = 0; i < SIZE - 3; i++)
	{
		for (int j = 0; j < SIZE - 3; j++)
		{
			if (board[i][j] == board[i + 1][j + 1] && board[i + 1][j + 1] == board[i + 2][j + 2] && board[i + 2][j + 2] == board[i + 3][j + 3] && board[i + 3][j + 3] == WHITE)			// 대각선 연속해서 4개
			{
				if (j == 0)				value[i + 4][j + 4] += 100;
				else if (j == SIZE - 4)	value[i - 1][j - 1] += 100;
				else					value[i - 1][j - 1] += 100, value[i + 4][j + 4] += 100;
			}
			else if (board[i][j] == board[i + 1][j + 1] && board[i + 1][j + 1] == board[i + 2][j + 2] && board[i + 2][j + 2] == board[i + 3][j + 3] && board[i + 3][j + 3] == BLACK)	// 대각선 연속해서 4개
			{
				if (j == 0)				value[i + 4][j + 4] += 95;
				else if (j == SIZE - 4)	value[i - 1][j - 1] += 95;
				else					value[i - 1][j - 1] += 95, value[i + 4][j + 4] += 95;
			}
		}
	}

	for (int j = 0; j < SIZE; j++)
	{
		for (int i = 0; i < SIZE - 3; i++)
		{
			if (board[i][j] == board[i + 1][j] && board[i + 1][j] == board[i + 2][j] && board[i + 2][j] == board[i + 3][j] && board[i + 3][j] == WHITE)			// 세로로 연속해서 4개
			{
				if (i == 0)				value[i + 4][j] += 100;
				else if (i == SIZE - 4)	value[i - 1][j] += 100;
				else					value[i - 1][j] += 100, value[i + 4][j] += 100;
			}
			else if (board[i][j] == board[i + 1][j] && board[i + 1][j] == board[i + 2][j] && board[i + 2][j] == board[i + 3][j] && board[i + 3][j] == BLACK)	// 세로로 연속해서 4개
			{
				if (i == 0)				value[i + 4][j] += 95;
				else if (i == SIZE - 4)	value[i - 1][j] += 95;
				else					value[i - 1][j] += 95, value[i + 4][j] += 95;
			}
		}
	}

	for (int i = 3; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE - 3; j++)
		{
			if (board[i][j] == board[i - 1][j + 1] && board[i - 1][j + 1] == board[i - 2][j + 2] && board[i - 2][j + 2] == board[i - 3][j + 3] && board[i - 3][j + 3] == WHITE)			// 대각선 연속해서 4개
			{
				if (j == 0)				value[i - 4][j + 4] += 100;
				else if (j == SIZE - 4)	value[i + 1][j - 1] += 100;
				else					value[i + 1][j - 1] += 100, value[i - 4][j + 4] += 100;
			}
			else if (board[i][j] == board[i - 1][j + 1] && board[i - 1][j + 1] == board[i - 2][j + 2] && board[i - 2][j + 2] == board[i - 3][j + 3] && board[i - 3][j + 3] == BLACK)	// 대각선 연속해서 4개
			{
				if (j == 0)				value[i - 4][j + 4] += 95;
				else if (j == SIZE - 4)	value[i + 1][j - 1] += 95;
				else					value[i + 1][j - 1] += 95, value[i - 4][j + 4] += 95;
			}
		}
	}
}

//==============================================================================================================//

void value_three()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE - 2; j++)
		{
			if (board[i][j] == board[i][j + 1] && board[i][j + 1] == board[i][j + 2] && board[i][j + 2] == WHITE)
			{
				if (j == 0)				value[i][j + 3] += 80;
				else if (j == SIZE - 3)	value[i][j - 1] += 80;
				else					value[i][j + 3] += 80, value[i][j - 1] += 80;
			}
			else if (board[i][j] == board[i][j + 1] && board[i][j + 1] == board[i][j + 2] && board[i][j + 2] == BLACK)
			{
				if (j == 0)				value[i][j + 3] += 70;
				else if (j == SIZE - 3)	value[i][j - 1] += 70;
				else					value[i][j + 3] += 70, value[i][j - 1] += 70;
			}
		}
	}

	for (int i = 0; i < SIZE - 2; i++)
	{
		for (int j = 0; j < SIZE - 2; j++)
		{
			if (board[i][j] == board[i + 1][j + 1] && board[i + 1][j + 1] == board[i + 2][j + 2] && board[i + 2][j + 2] == WHITE)
			{
				if (j == 0)				value[i + 3][j + 3] += 80;
				else if (j == SIZE - 3)	value[i - 1][j - 1] += 80;
				else					value[i + 3][j + 3] += 80, value[i - 1][j - 1] += 80;
			}
			else if (board[i][j] == board[i + 1][j + 1] && board[i + 1][j + 1] == board[i + 2][j + 2] && board[i + 2][j + 2] == BLACK)
			{
				if (j == 0)				value[i + 3][j + 3] += 70;
				else if (j == SIZE - 3)	value[i - 1][j - 1] += 70;
				else					value[i + 3][j + 3] += 70, value[i - 1][j - 1] += 70;
			}
		}
	}

	for (int j = 0; j < SIZE; j++)
	{
		for (int i = 0; i < SIZE - 2; i++)
		{
			if (board[i][j] == board[i + 1][j] && board[i + 1][j] == board[i + 2][j] && board[i + 2][j] == WHITE)
			{
				if (i == 0)				value[i + 3][j] += 80;
				else if (i == SIZE - 3)	value[i - 1][j] += 80;
				else					value[i + 3][j] += 80, value[i - 1][j] += 80;
			}
			if (board[i][j] == board[i + 1][j] && board[i + 1][j] == board[i + 2][j] && board[i + 2][j] == BLACK)
			{
				if (i == 0)				value[i + 3][j] += 70;
				else if (i == SIZE - 3)	value[i - 1][j] += 70;
				else					value[i + 3][j] += 70, value[i - 1][j] += 70;
			}
		}
	}

	for (int i = 2; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE - 2; j++)
		{
			if (board[i][j] == board[i - 1][j + 1] && board[i - 1][j + 1] == board[i - 2][j + 2] && board[i - 2][j + 2] == WHITE)
			{
				if (j == 0)				value[i - 3][j + 3] += 80;
				else if (j == SIZE - 3)	value[i + 1][j - 1] += 80;
				else					value[i - 3][j + 3] += 80, value[i + 1][j - 1] += 80;
			}
			else if (board[i][j] == board[i - 1][j + 1] && board[i - 1][j + 1] == board[i - 2][j + 2] && board[i - 2][j + 2] == BLACK)
			{
				if (j == 0)				value[i - 3][j + 3] += 70;
				else if (j == SIZE - 3)	value[i + 1][j - 1] += 70;
				else					value[i - 3][j + 3] += 70, value[i + 1][j - 1] += 70;
			}
		}
	}
}

//==============================================================================================================//

void value_two()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE - 1; j++)
		{
			if (board[i][j] == board[i][j + 1] && board[i][j + 1] == WHITE)
			{
				if (j == 0)				value[i][j + 2] += 60;
				else if (j == SIZE - 2)	value[i][j - 1] += 60;
				else					value[i][j + 2] += 60, value[i][j - 1] += 60;
			}
			else if (board[i][j] == board[i][j + 1] && board[i][j + 1] == BLACK)
			{
				if (j == 0)				value[i][j + 2] += 55;
				else if (j == SIZE - 2)	value[i][j - 1] += 55;
				else					value[i][j + 2] += 55, value[i][j - 1] += 55;
			}
		}
	}

	for (int i = 0; i < SIZE - 1; i++)
	{
		for (int j = 0; j < SIZE - 1; j++)
		{
			if (board[i][j] == board[i + 1][j + 1] && board[i + 1][j + 1] == WHITE)
			{
				if (j == 0)				value[i + 2][j + 2] += 60;
				else if (j == SIZE - 2)	value[i - 1][j - 1] += 60;
				else					value[i + 2][j + 2] += 60, value[i - 1][j - 1] += 60;
			}
			else if (board[i][j] == board[i + 1][j + 1] && board[i + 1][j + 1] == BLACK)
			{
				if (j == 0)				value[i + 2][j + 2] += 55;
				else if (j == SIZE - 2)	value[i - 1][j - 1] += 55;
				else					value[i + 2][j + 2] += 55, value[i - 1][j - 1] += 55;
			}
		}
	}

	for (int j = 0; j < SIZE; j++)
	{
		for (int i = 0; i < SIZE - 1; i++)
		{
			if (board[i][j] == board[i + 1][j] && board[i + 1][j] == WHITE)
			{
				if (i == 0)				value[i + 2][j] += 60;
				else if (i == SIZE - 2)	value[i - 1][j] += 60;
				else					value[i + 2][j] += 60, value[i - 1][j] += 60;
			}
			if (board[i][j] == board[i + 1][j] && board[i + 1][j] == BLACK)
			{
				if (i == 0)				value[i + 2][j] += 55;
				else if (i == SIZE - 2)	value[i - 1][j] += 55;
				else					value[i + 2][j] += 55, value[i - 1][j] += 55;
			}
		}
	}

	for (int i = 1; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE - 1; j++)
		{
			if (board[i][j] == board[i - 1][j + 1] && board[i - 1][j + 1] == WHITE)
			{
				if (j == 0)				value[i - 2][j + 2] += 60;
				else if (j == SIZE - 2)	value[i + 1][j - 1] += 60;
				else					value[i - 2][j + 2] += 60, value[i + 1][j - 1] += 60;
			}
			else if (board[i][j] == board[i - 1][j + 1] && board[i - 1][j + 1] == BLACK)
			{
				if (j == 0)				value[i - 2][j + 2] += 55;
				else if (j == SIZE - 2)	value[i + 1][j - 1] += 55;
				else					value[i - 2][j + 2] += 55, value[i + 1][j - 1] += 55;
			}
		}
	}
}

//==============================================================================================================//

void value_one()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (board[i][j] == WHITE)
			{
				if (j == 0)				value[i][j + 1] += 20;
				else if (j == SIZE - 1)	value[i][j - 1] += 20;
				else					value[i][j + 1] += 20, value[i][j - 1] += 20, value[i + 1][j + 1] += 20, value[i - 1][j + 1] += 20, value[i - 1][j - 1] += 20, value[i + 1][j - 1] += 20;
			}
			else if (board[i][j] == BLACK)
			{
				if (j == 0)				value[i][j + 1] += 15;
				else if (j == SIZE - 1)	value[i][j - 1] += 15;
				else					value[i][j + 1] += 15, value[i][j - 1] += 15, value[i + 1][j + 1] += 15, value[i - 1][j + 1] += 15, value[i - 1][j - 1] += 15, value[i + 1][j - 1] += 15;
			}
		}
	}

	for (int j = 0; j < SIZE; j++)
	{
		for (int i = 0; i < SIZE; i++)
		{
			if (board[i][j] == WHITE)
			{
				if (i == 0)				value[i + 1][j] += 20;
				else if (i == SIZE - 1)	value[i - 1][j] += 20;
				else					value[i + 1][j] += 20, value[i - 1][j] += 20;
			}
			if (board[i][j] == BLACK)
			{
				if (i == 0)				value[i + 1][j] += 15;
				else if (i == SIZE - 1)	value[i - 1][j] += 15;
				else					value[i + 1][j] += 15, value[i - 1][j] += 15;
			}
		}
	}
}

//==============================================================================================================//

void get_action()
{
	value_init();
	value_update();

	int max = 0;
	int cnt = 0;
	int k = 0;
	int chosen;

	//print_value();
	//getch();

	int * actions;

	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
		{
			if (value[i][j] >= max)
				max = value[i][j];
		}

	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
		{
			if (value[i][j] == max)
				cnt++;
		}

	actions = (int *)malloc(cnt * sizeof(int));

	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
		{
			if (value[i][j] == max)
				actions[k++] = i * 19 + j;
		}

	chosen = actions[random(cnt)];
	board[chosen / SIZE][chosen%SIZE] = flag;
	flag = 3 - flag;
	/*gotoxy(0, 19);
	for (int i = 0; i < k; i++)
		printf(" %d,", actions[i]);*/
}

//==============================================================================================================//

void value_update()
{
	value_four();
	value_three();
	value_two();
	value_one();
}

//==============================================================================================================//

void print_value()
{
	gotoxy(0, 20);
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
			printf(" %4d", value[j][i]);
		printf("\n");
	}
}