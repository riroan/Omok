#include"Environment.h"
#include<iostream>
#include<conio.h>
#pragma warning(disable:4996)

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACE 32
#define SIZE 19
#define BLACK 1
#define WHITE 2
#define NONE 0

//==============================================================================================================//

int board[SIZE][SIZE] = { NONE };
int flag = BLACK;

//==============================================================================================================//

extern void gotoxy(int x, int y);

//==============================================================================================================//

Environment::Environment(int size)
	:px(0), py(0), win(0), size_(size)
{}

//==============================================================================================================//

void Environment::Init()
{
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			board[i][j] = 0;
	win = 0;
}

//==============================================================================================================//

void Environment::draw_board2()
{
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
		{
			gotoxy(2 * i, j);	printf(". ");
		}

	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
		{
			if (board[i][j] == BLACK)
			{
				gotoxy(2 * i, j);	printf("¡Û");
			}
			else if (board[i][j] == WHITE)
			{
				gotoxy(2 * i, j);	printf("¡Ü");
			}
		}
}

//==============================================================================================================//

void Environment::draw_board()
{
	gotoxy(0, 0);
	printf("¦£ ¦¨ ¦¨ ¦¨ ¦¨ ¦¨ ¦¨ ¦¨ ¦¨ ¦¨ ¦¨ ¦¨ ¦¨ ¦¨ ¦¨ ¦¨ ¦¨ ¦¨ ¦¤\n");
	for (int i = 0; i < 17; i++)
		printf("¦§ ¦« ¦« ¦« ¦« ¦« ¦« ¦« ¦« ¦« ¦« ¦« ¦« ¦« ¦« ¦« ¦« ¦« ¦©\n");
	printf("¦¦ ¦ª ¦ª ¦ª ¦ª ¦ª ¦ª ¦ª ¦ª ¦ª ¦ª ¦ª ¦ª ¦ª ¦ª ¦ª ¦ª ¦ª ¦¥\n");
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
		{
			if (board[i][j] == BLACK)
			{
				gotoxy(2 * i, j);	printf("¡Û");
			}
			else if (board[i][j] == WHITE)
			{
				gotoxy(2 * i, j);	printf("¡Ü");
			}
		}
}

//==============================================================================================================//

void Environment::draw_dol()
{
	gotoxy(px, py);
	if (flag == BLACK)
		printf("¡Û");
	else
		printf("¡Ü");
}

//==============================================================================================================//

void Environment::move_dol()
{
	char ch;
	ch = getch();
	if (ch == LEFT || ch == RIGHT || ch == UP || ch == DOWN || ch == SPACE)
	{
		switch (ch)
		{
		case LEFT:
			px -= 2;
			break;
		case RIGHT:
			px += 2;
			break;
		case UP:
			py -= 1;
			break;
		case DOWN:
			py += 1;
			break;
		case SPACE:
			put_dol();
			break;
		}
	}
	if (px < 0)	px = 0;
	if (py < 0)	py = 0;
	if (px > 2 * (SIZE - 1))	px = 36;
	if (py > SIZE - 1)	py = 18;
}

//==============================================================================================================//

void Environment::erase_dol()
{
	gotoxy(px, py);	printf("  ");
}

//==============================================================================================================//

void Environment::put_dol()
{
	if (board[px / 2][py] == 0)
	{
		if (flag == BLACK)
		{
			board[px / 2][py] = BLACK;
			flag = 3 - flag;
		}
		else if (flag == WHITE)
		{
			board[px / 2][py] = WHITE;
			flag = 3 - flag;
		}
	}
}

//==============================================================================================================//

void Environment::who_win()
{
	check_width();
	check_height();
	check_leftcross();
	check_rightcross();
}

//==============================================================================================================//

void Environment::check_height()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 2; j < SIZE - 2; j++)
		{
			if (board[i][j - 2] == board[i][j - 1] && board[i][j - 1] == board[i][j] && board[i][j] == board[i][j + 1] && board[i][j + 1] == board[i][j + 2])
			{
				if (board[i][j] == BLACK)
					win = BLACK;
				else if (board[i][j] == WHITE)
					win = WHITE;
			}
		}
	}
}

//==============================================================================================================//

void Environment::check_width()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 2; j < SIZE - 2; j++)
		{
			if (board[j - 2][i] == board[j - 1][i] && board[j - 1][i] == board[j][i] && board[j][i] == board[j + 1][i] && board[j + 1][i] == board[j + 2][i])
			{
				if (board[j][i] == BLACK)
					win = BLACK;
				else if (board[j][i] == WHITE)
					win = WHITE;
			}
		}
	}
}

//==============================================================================================================//

void Environment::check_leftcross()
{
	for (int i = 2; i < SIZE - 2; i++)
	{
		for (int j = 2; j < SIZE - 2; j++)
		{
			if (board[i - 2][j - 2] == board[i - 1][j - 1] && board[i - 1][j - 1] == board[i][j] && board[i][j] == board[i + 1][j + 1] && board[i + 1][j + 1] == board[i + 2][j + 2])
			{
				if (board[i][j] == BLACK)
					win = BLACK;
				else if (board[i][j] == WHITE)
					win = WHITE;
			}
		}
	}
}

//==============================================================================================================//

void Environment::check_rightcross()
{
	for (int i = 2; i < SIZE - 2; i++)
	{
		for (int j = 2; j < SIZE - 2; j++)
		{
			if (board[i - 2][j + 2] == board[i - 1][j + 1] && board[i - 1][j + 1] == board[i][j] && board[i][j] == board[i + 1][j - 1] && board[i + 1][j - 1] == board[i + 2][j - 2])
			{
				if (board[i][j] == BLACK)
					win = BLACK;
				else if (board[i][j] == WHITE)
					win = WHITE;
			}
		}
	}
}

//==============================================================================================================//

void Environment::print_win()
{
	gotoxy(38, 5);
	if (win == BLACK)
		printf("Èæ½Â¸®!");
	else if (win == WHITE)
		printf("¹é½Â¸®!");
	gotoxy(0, 19);
}