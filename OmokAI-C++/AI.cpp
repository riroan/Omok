#include"AI.h"
#include<cstdio>
#include<cstdlib>
#pragma warning(disable:4996)

#define SIZE 19
#define BLACK 1
#define WHITE 2
#define NONE 0
#define random(n) (rand()%n)

//==============================================================================================================//

extern int board[SIZE][SIZE];
extern int flag;
extern void gotoxy(int x, int y);

//==============================================================================================================//

AI::AI(int size_)
	:size(size_)
{
	value = (double **)malloc(size_ * sizeof(double *));
	for (int i = 0; i < size_; i++)
		value[i] = (double *)malloc(size_ * sizeof(double));
}

//==============================================================================================================//

AI::~AI()
{
	for (int i = 0; i < size; i++)
		free(value[i]);
	free(value);
}

//==============================================================================================================//

void AI::value_init()
{
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			value[i][j] = 0.0;

	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
		{
			if (board[i][j] != NONE)
				value[i][j] = -9.0;
		}
}

//==============================================================================================================//

void AI::value_four()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE - 3; j++)
		{
			if (board[i][j] == board[i][j + 1] && board[i][j + 1] == board[i][j + 2] && board[i][j + 2] == board[i][j + 3] && board[i][j + 3] == WHITE)			// 가로로 연속해서 4개
			{
				if (j == 0)				value[i][j + 4] += 1.0;
				else if (j == SIZE - 4)	value[i][j - 1] += 1.0;
				else					value[i][j - 1] += 1.0, value[i][j + 4] += 1.0;
			}
			else if (board[i][j] == board[i][j + 1] && board[i][j + 1] == board[i][j + 2] && board[i][j + 2] == board[i][j + 3] && board[i][j + 3] == BLACK)	// 가로로 연속해서 4개
			{
				if (j == 0)				value[i][j + 4] += 0.95;
				else if (j == SIZE - 4)	value[i][j - 1] += 0.95;
				else					value[i][j - 1] += 0.95, value[i][j + 4] += 0.95;
			}
		}
	}

	for (int i = 0; i < SIZE - 3; i++)
	{
		for (int j = 0; j < SIZE - 3; j++)
		{
			if (board[i][j] == board[i + 1][j + 1] && board[i + 1][j + 1] == board[i + 2][j + 2] && board[i + 2][j + 2] == board[i + 3][j + 3] && board[i + 3][j + 3] == WHITE)			// 대각선 연속해서 4개
			{
				if (i == 0 && j == SIZE - 4)			continue;
				else if (j == 0 && i == SIZE - 4)		continue;
				else if (i == 0 || j == 0)				value[i + 4][j + 4] += 1.0;
				else if (i == SIZE - 4 || j == SIZE - 4)	value[i - 1][j - 1] += 1.0;
				else					value[i - 1][j - 1] += 1.0, value[i + 4][j + 4] += 1.0;
			}
			else if (board[i][j] == board[i + 1][j + 1] && board[i + 1][j + 1] == board[i + 2][j + 2] && board[i + 2][j + 2] == board[i + 3][j + 3] && board[i + 3][j + 3] == BLACK)	// 대각선 연속해서 4개
			{
				if (j == 0 && i == SIZE - 4)				continue;
				else if (i == 0 && j == SIZE - 4)			continue;
				else if (j == 0 || i == 0)					value[i + 4][j + 4] += 0.95;
				else if (i == SIZE - 4 || j == SIZE - 4)	value[i - 1][j - 1] += 0.95;
				else					value[i - 1][j - 1] += 0.95, value[i + 4][j + 4] += 0.95;
			}
		}
	}

	for (int j = 0; j < SIZE; j++)
	{
		for (int i = 0; i < SIZE - 3; i++)
		{
			if (board[i][j] == board[i + 1][j] && board[i + 1][j] == board[i + 2][j] && board[i + 2][j] == board[i + 3][j] && board[i + 3][j] == WHITE)			// 세로로 연속해서 4개
			{
				if (i == 0)				value[i + 4][j] += 1.0;
				else if (i == SIZE - 4)	value[i - 1][j] += 1.0;
				else					value[i - 1][j] += 1.0, value[i + 4][j] += 1.0;
			}
			else if (board[i][j] == board[i + 1][j] && board[i + 1][j] == board[i + 2][j] && board[i + 2][j] == board[i + 3][j] && board[i + 3][j] == BLACK)	// 세로로 연속해서 4개
			{
				if (i == 0)				value[i + 4][j] += 0.95;
				else if (i == SIZE - 4)	value[i - 1][j] += 0.95;
				else					value[i - 1][j] += 0.95, value[i + 4][j] += 0.95;
			}
		}
	}

	for (int i = 3; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE - 3; j++)
		{
			if (board[i][j] == board[i - 1][j + 1] && board[i - 1][j + 1] == board[i - 2][j + 2] && board[i - 2][j + 2] == board[i - 3][j + 3] && board[i - 3][j + 3] == WHITE)			// 대각선 연속해서 4개
			{
				if (j == 0 && i == 3)						continue;
				else if (i == SIZE - 1 && j == SIZE - 4)	continue;
				else if (j == 0 || i == SIZE - 1)			value[i - 4][j + 4] += 1.0;
				else if (i == 3 || j == SIZE - 4)			value[i + 1][j - 1] += 1.0;
				else										value[i + 1][j - 1] += 1.0, value[i - 4][j + 4] += 1.0;
			}
			else if (board[i][j] == board[i - 1][j + 1] && board[i - 1][j + 1] == board[i - 2][j + 2] && board[i - 2][j + 2] == board[i - 3][j + 3] && board[i - 3][j + 3] == BLACK)	// 대각선 연속해서 4개
			{
				if (j == 0 && i == 3)						continue;
				else if (i == SIZE - 1 && j == SIZE - 4)	continue;
				else if (j == 0 || i == SIZE - 1)			value[i - 4][j + 4] += 0.95;
				else if (i == 3 || j == SIZE - 4)			value[i + 1][j - 1] += 0.95;
				else										value[i + 1][j - 1] += 0.95, value[i - 4][j + 4] += 0.95;
			}
		}
	}
}

//==============================================================================================================//

void AI::value_three()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE - 2; j++)
		{
			if (board[i][j] == board[i][j + 1] && board[i][j + 1] == board[i][j + 2] && board[i][j + 2] == WHITE)
			{
				if (j == 0)				value[i][j + 3] += 0.8;
				else if (j == SIZE - 3)	value[i][j - 1] += 0.8;
				else					value[i][j + 3] += 0.8, value[i][j - 1] += 0.8;
			}
			else if (board[i][j] == board[i][j + 1] && board[i][j + 1] == board[i][j + 2] && board[i][j + 2] == BLACK)
			{
				if (j == 0)				value[i][j + 3] += 0.7;
				else if (j == SIZE - 3)	value[i][j - 1] += 0.7;
				else					value[i][j + 3] += 0.7, value[i][j - 1] += 0.7;
			}
		}
	}

	for (int i = 0; i < SIZE - 2; i++)
	{
		for (int j = 0; j < SIZE - 2; j++)
		{
			if (board[i][j] == board[i + 1][j + 1] && board[i + 1][j + 1] == board[i + 2][j + 2] && board[i + 2][j + 2] == WHITE)
			{
				if (j == 0 && i == SIZE - 3)				continue;
				else if (j == SIZE - 3 && i == 0)			continue;
				else if (j == 0 || i == 0)					value[i + 3][j + 3] += 0.8;
				else if (j == SIZE - 3 || i == SIZE - 3)	value[i - 1][j - 1] += 0.8;
				else										value[i + 3][j + 3] += 0.8, value[i - 1][j - 1] += 0.8;
			}
			else if (board[i][j] == board[i + 1][j + 1] && board[i + 1][j + 1] == board[i + 2][j + 2] && board[i + 2][j + 2] == BLACK)
			{
				if (j == 0 && i == SIZE - 3)				continue;
				else if (j == SIZE - 3 && i == 0)			continue;
				else if (j == 0 || i == 0)					value[i + 3][j + 3] += 0.7;
				else if (j == SIZE - 3 || i == SIZE - 3)	value[i - 1][j - 1] += 0.7;
				else					value[i + 3][j + 3] += 0.7, value[i - 1][j - 1] += 0.7;
			}
		}
	}

	for (int j = 0; j < SIZE; j++)
	{
		for (int i = 0; i < SIZE - 2; i++)
		{
			if (board[i][j] == board[i + 1][j] && board[i + 1][j] == board[i + 2][j] && board[i + 2][j] == WHITE)
			{
				if (i == 0)				value[i + 3][j] += 0.8;
				else if (i == SIZE - 3)	value[i - 1][j] += 0.8;
				else					value[i + 3][j] += 0.8, value[i - 1][j] += 0.8;
			}
			if (board[i][j] == board[i + 1][j] && board[i + 1][j] == board[i + 2][j] && board[i + 2][j] == BLACK)
			{
				if (i == 0)				value[i + 3][j] += 0.7;
				else if (i == SIZE - 3)	value[i - 1][j] += 0.7;
				else					value[i + 3][j] += 0.7, value[i - 1][j] += 0.7;
			}
		}
	}

	for (int i = 2; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE - 2; j++)
		{
			if (board[i][j] == board[i - 1][j + 1] && board[i - 1][j + 1] == board[i - 2][j + 2] && board[i - 2][j + 2] == WHITE)
			{
				if (j == 0 && i == 2)								continue;
				else if (i == SIZE - 1 && j == SIZE - 3)		continue;
				else if (j == 0 || i == SIZE - 1)				value[i - 3][j + 3] += 0.8;
				else if (j == SIZE - 3 || i == 2)				value[i + 1][j - 1] += 0.8;
				else											value[i - 3][j + 3] += 0.8, value[i + 1][j - 1] += 0.8;
			}
			else if (board[i][j] == board[i - 1][j + 1] && board[i - 1][j + 1] == board[i - 2][j + 2] && board[i - 2][j + 2] == BLACK)
			{
				if (j == 0 && i == 2)							continue;
				else if (i == SIZE - 1 && j == SIZE - 3)		continue;
				else if (j == 0 || i == SIZE - 1)				value[i - 3][j + 3] += 0.7;
				else if (j == SIZE - 3 || i == 2)				value[i + 1][j - 1] += 0.7;
				else					value[i - 3][j + 3] += 0.7, value[i + 1][j - 1] += 0.7;
			}
		}
	}
}

//==============================================================================================================//

void AI::value_two()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE - 1; j++)
		{
			if (board[i][j] == board[i][j + 1] && board[i][j + 1] == WHITE)
			{
				if (j == 0)				value[i][j + 2] += 0.6;
				else if (j == SIZE - 2)	value[i][j - 1] += 0.6;
				else					value[i][j + 2] += 0.6, value[i][j - 1] += 0.6;
			}
			else if (board[i][j] == board[i][j + 1] && board[i][j + 1] == BLACK)
			{
				if (j == 0)				value[i][j + 2] += 0.55;
				else if (j == SIZE - 2)	value[i][j - 1] += 0.55;
				else					value[i][j + 2] += 0.55, value[i][j - 1] += 0.55;
			}
		}
	}

	for (int i = 0; i < SIZE - 1; i++)
	{
		for (int j = 0; j < SIZE - 1; j++)
		{
			if (board[i][j] == board[i + 1][j + 1] && board[i + 1][j + 1] == WHITE)
			{
				if (i == SIZE - 2 && j == 0)				continue;
				else if (i == 0 && j == SIZE - 2)			continue;
				else if (j == 0 || i == 0)					value[i + 2][j + 2] += 0.6;
				else if (i == SIZE - 2 || j == SIZE - 2)	value[i - 1][j - 1] += 0.6;
				else										value[i + 2][j + 2] += 0.6, value[i - 1][j - 1] += 0.6;
			}
			else if (board[i][j] == board[i + 1][j + 1] && board[i + 1][j + 1] == BLACK)
			{
				if (i == SIZE - 2 && j == 0)				continue;
				else if (i == 0 && j == SIZE - 2)			continue;
				else if (j == 0 || i == 0)					value[i + 2][j + 2] += 0.55;
				else if (i == SIZE - 2 || j == SIZE - 2)	value[i - 1][j - 1] += 0.55;
				else										value[i + 2][j + 2] += 0.55, value[i - 1][j - 1] += 0.55;
			}
		}
	}

	for (int j = 0; j < SIZE; j++)
	{
		for (int i = 0; i < SIZE - 1; i++)
		{
			if (board[i][j] == board[i + 1][j] && board[i + 1][j] == WHITE)
			{
				if (i == 0)				value[i + 2][j] += 0.6;
				else if (i == SIZE - 2)	value[i - 1][j] += 0.6;
				else					value[i + 2][j] += 0.6, value[i - 1][j] += 0.6;
			}
			if (board[i][j] == board[i + 1][j] && board[i + 1][j] == BLACK)
			{
				if (i == 0)				value[i + 2][j] += 0.55;
				else if (i == SIZE - 2)	value[i - 1][j] += 0.55;
				else					value[i + 2][j] += 0.55, value[i - 1][j] += 0.55;
			}
		}
	}

	for (int i = 1; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE - 1; j++)
		{
			if (board[i][j] == board[i - 1][j + 1] && board[i - 1][j + 1] == WHITE)
			{
				if (i == 1 && j == 0)						continue;
				else if (i == SIZE - 1 && j == SIZE - 2)	continue;
				else if (i == SIZE - 1 || j == 0)			value[i - 2][j + 2] += 0.6;
				else if (i == 1 || j == SIZE - 2)			value[i + 1][j - 1] += 0.6;
				else					value[i - 2][j + 2] += 0.6, value[i + 1][j - 1] += 0.6;
			}
			else if (board[i][j] == board[i - 1][j + 1] && board[i - 1][j + 1] == BLACK)
			{
				if (i == 1 && j == 0)						continue;
				else if (i == SIZE - 1 && j == SIZE - 2)	continue;
				else if (i == SIZE - 1 || j == 0)			value[i - 2][j + 2] += 0.55;
				else if (i == 1 || j == SIZE - 2)			value[i + 1][j - 1] += 0.55;
				else					value[i - 2][j + 2] += 0.55, value[i + 1][j - 1] += 0.55;
			}
		}
	}
}

//==============================================================================================================//

void AI::value_one()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (board[i][j] == WHITE)
			{
				if (i == 0 && j == 0)						value[i][j + 1] += 0.2, value[i + 1][j] += 0.2, value[i + 1][j + 1] += 0.2;
				else if (i == 0 && j == SIZE - 1)			value[i + 1][j] += 0.2, value[i][j - 1] += 0.2, value[i + 1][j - 1] += 0.2;
				else if (i == SIZE - 1 && j == SIZE - 1)	value[i - 1][j] += 0.2, value[i][j - 1] += 0.2, value[i - 1][j - 1] += 0.2;
				else if (i == SIZE - 1 && j == 0)			value[i - 1][j] += 0.2, value[i][j + 1] += 0.2, value[i - 1][j + 1] += 0.2;
				else if (i == 0)							value[i + 1][j] += 0.2, value[i][j + 1] += 0.2, value[i][j - 1] += 0.2;
				else if (j == 0)							value[i + 1][j] += 0.2, value[i - 1][j] += 0.2, value[i][j + 1] += 0.2;
				else if (i == SIZE - 1)						value[i - 1][j] += 0.2, value[i][j + 1] += 0.2, value[i][j - 1] += 0.2;
				else if (j == SIZE - 1)						value[i + 1][j] += 0.2, value[i - 1][j] += 0.2, value[i][j - 1] += 0.2;
				else					value[i][j + 1] += 0.2, value[i][j - 1] += 0.2, value[i + 1][j + 1] += 0.2, value[i - 1][j + 1] += 0.2, value[i - 1][j - 1] += 0.2, value[i + 1][j - 1] += 0.2;
			}
			else if (board[i][j] == BLACK)
			{
				if (i == 0 && j == 0)						value[i][j + 1] += 0.15, value[i + 1][j] += 0.15, value[i + 1][j + 1] += 0.15;
				else if (i == 0 && j == SIZE - 1)			value[i + 1][j] += 0.15, value[i][j - 1] += 0.15, value[i + 1][j - 1] += 0.15;
				else if (i == SIZE - 1 && j == SIZE - 1)	value[i - 1][j] += 0.15, value[i][j - 1] += 0.15, value[i - 1][j - 1] += 0.15;
				else if (i == SIZE - 1 && j == 0)			value[i - 1][j] += 0.15, value[i][j + 1] += 0.15, value[i - 1][j + 1] += 0.15;
				else if (i == 0)							value[i + 1][j] += 0.15, value[i][j + 1] += 0.15, value[i][j - 1] += 0.15;
				else if (j == 0)							value[i + 1][j] += 0.15, value[i - 1][j] += 0.15, value[i][j + 1] += 0.15;
				else if (i == SIZE - 1)						value[i - 1][j] += 0.15, value[i][j + 1] += 0.15, value[i][j - 1] += 0.15;
				else if (j == SIZE - 1)						value[i + 1][j] += 0.15, value[i - 1][j] += 0.15, value[i][j - 1] += 0.15;
				else					value[i][j + 1] += 0.15, value[i][j - 1] += 0.15, value[i + 1][j + 1] += 0.15, value[i - 1][j + 1] += 0.15, value[i - 1][j - 1] += 0.15, value[i + 1][j - 1] += 0.15;
			}
		}
	}
}

//==============================================================================================================//

void AI::get_action()
{
	value_init();
	value_update();

	double max = 0;
	int cnt = 0;
	int k = 0;
	int chosen;

	print_value();							// 현재 value를 보고싶을때
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

void AI::value_update()
{
	value_four();
	value_three();
	value_two();
	value_one();
}

//==============================================================================================================//

void AI::print_value()
{
	gotoxy(0, 20);
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
			printf(" %.2f", value[j][i]);
		printf("\n");
	}
}