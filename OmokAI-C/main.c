// OMOK GAME
//==============================================================================================================//
// 2018-04-07
// 단순한 인공지능 탑재
// 현재 오목판을 분석하여 가치함수를 설정함
// 가치함수중에서 가장 큰 값을 가지는 위치에 착수함
// 가치함수의 최댓값이 여러개일경우 랜덤한 곳에 착수함
// 모니터에 따라 UI가 이상하게 보일수 있음 -> main 함수에 있는 draw_board2() 사용

//==============================================================================================================//

#include"good.h"
#pragma warning(disable:4996)

//==============================================================================================================//

void draw_board();
void draw_dol();
void move_dol();
void erase_dol();
void put_dol();
void who_win();
void check_width();				// 가로 5목 확인
void check_height();			// 세로 5목 확인
void check_leftcross();			// 좌상방향 대각선 5목 확인
void check_rightcross();		// 우상방향 대각선 5목 확인
void print_win();
void Init();
void draw_board2();
extern void get_action();

//==============================================================================================================//

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

int board[SIZE][SIZE] = { NONE };		// value가 1이면 흑돌, 2면 백돌, 0이면 빈공간
int px;
int py;
int flag = BLACK;						// flag가 1이면 흑돌, 2면 백돌
int win;								// win이 1이면 흑돌 승, 2면 백돌 승

//==============================================================================================================//

int main()
{
	system("mode con:cols=60 lines=21");
	system("title MyOmok");
	setcursortype(NOCURSOR);
	randomize();
	Init();

	while (1)
	{
		draw_board();						// UI가 이상하게 보일경우 draw_board2를 사용
		//draw_board2();

		who_win();
		if (win != 0)
			break;

		if (flag == BLACK)
		{
			draw_dol();
			move_dol();
			erase_dol();
		}
		else if (flag == WHITE)
			get_action();
	}
	print_win();
	system("pause");
}

//==============================================================================================================//

void Init()
{
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			board[i][j] = 0;
	win = 0;
}

//==============================================================================================================//

void draw_board2()
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
				gotoxy(2 * i, j);	printf("○");
			}
			else if (board[i][j] == WHITE)
			{
				gotoxy(2 * i, j);	printf("●");
			}
		}
}

//==============================================================================================================//

void draw_board()
{
	int i, j;
	gotoxy(0, 0);
	printf("┌ ┬ ┬ ┬ ┬ ┬ ┬ ┬ ┬ ┬ ┬ ┬ ┬ ┬ ┬ ┬ ┬ ┬ ┐\n");
	for (i = 0; i < 17; i++)
		printf("├ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┤\n");
	printf("└ ┴ ┴ ┴ ┴ ┴ ┴ ┴ ┴ ┴ ┴ ┴ ┴ ┴ ┴ ┴ ┴ ┴ ┘\n");
	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++)
		{
			if (board[i][j] == BLACK)
			{
				gotoxy(2 * i, j);	printf("○");
			}
			else if (board[i][j] == WHITE)
			{
				gotoxy(2 * i, j);	printf("●");
			}
		}
}

//==============================================================================================================//

void draw_dol()
{
	gotoxy(px, py);
	if (flag == BLACK)
		printf("○");
	else
		printf("●");
}

//==============================================================================================================//

void move_dol()
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

void erase_dol()
{
	gotoxy(px, py);	printf("  ");
}

//==============================================================================================================//

void put_dol()
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

void who_win()
{
	check_width();
	check_height();
	check_leftcross();
	check_rightcross();
}

//==============================================================================================================//

void check_height()
{
	int i, j;
	for (i = 0; i < SIZE; i++)
	{
		for (j = 2; j < SIZE - 2; j++)
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

void check_width()
{
	int i, j;
	for (i = 0; i < SIZE; i++)
	{
		for (j = 2; j < SIZE - 2; j++)
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

void check_leftcross()
{
	int i, j;
	for (i = 2; i < SIZE - 2; i++)
	{
		for (j = 2; j < SIZE - 2; j++)
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

void check_rightcross()
{
	int i, j;
	for (i = 2; i < SIZE - 2; i++)
	{
		for (j = 2; j < SIZE - 2; j++)
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

void print_win()
{
	gotoxy(38, 5);
	if (win == BLACK)
		printf("흑승리!");
	else if (win == WHITE)
		printf("백승리!");
	gotoxy(0, 19);
}