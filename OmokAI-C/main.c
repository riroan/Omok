// OMOK GAME
//==============================================================================================================//
// 2018-04-07
// �ܼ��� �ΰ����� ž��
// ���� �������� �м��Ͽ� ��ġ�Լ��� ������
// ��ġ�Լ��߿��� ���� ū ���� ������ ��ġ�� ������
// ��ġ�Լ��� �ִ��� �������ϰ�� ������ ���� ������
// ����Ϳ� ���� UI�� �̻��ϰ� ���ϼ� ���� -> main �Լ��� �ִ� draw_board2() ���

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
void check_width();				// ���� 5�� Ȯ��
void check_height();			// ���� 5�� Ȯ��
void check_leftcross();			// �»���� �밢�� 5�� Ȯ��
void check_rightcross();		// ������ �밢�� 5�� Ȯ��
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

int board[SIZE][SIZE] = { NONE };		// value�� 1�̸� �浹, 2�� �鵹, 0�̸� �����
int px;
int py;
int flag = BLACK;						// flag�� 1�̸� �浹, 2�� �鵹
int win;								// win�� 1�̸� �浹 ��, 2�� �鵹 ��

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
		draw_board();						// UI�� �̻��ϰ� ���ϰ�� draw_board2�� ���
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
				gotoxy(2 * i, j);	printf("��");
			}
			else if (board[i][j] == WHITE)
			{
				gotoxy(2 * i, j);	printf("��");
			}
		}
}

//==============================================================================================================//

void draw_board()
{
	int i, j;
	gotoxy(0, 0);
	printf("�� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� ��\n");
	for (i = 0; i < 17; i++)
		printf("�� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� ��\n");
	printf("�� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� ��\n");
	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++)
		{
			if (board[i][j] == BLACK)
			{
				gotoxy(2 * i, j);	printf("��");
			}
			else if (board[i][j] == WHITE)
			{
				gotoxy(2 * i, j);	printf("��");
			}
		}
}

//==============================================================================================================//

void draw_dol()
{
	gotoxy(px, py);
	if (flag == BLACK)
		printf("��");
	else
		printf("��");
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
		printf("��¸�!");
	else if (win == WHITE)
		printf("��¸�!");
	gotoxy(0, 19);
}