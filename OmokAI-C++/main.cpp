// OMOK GAME
//==============================================================================================================//
// 2018-04-07
// ver 1.0
// �ܼ��� �ΰ����� ž��
// ���� �������� �м��Ͽ� ��ġ�Լ��� ������
// ��ġ�Լ��߿��� ���� ū ���� ������ ��ġ�� ������
// ��ġ�Լ��� �ִ��� �������ϰ�� ������ ���� ������
// ����Ϳ� ���� UI�� �̻��ϰ� ���ϼ� ���� -> main �Լ��� �ִ� draw_board2() ���

// 2018-04-08
// ver 1.1
// ��ġ�Լ����� ������ ����� �������� ���� ������
// c++���� �߰�
// �ΰ�����vs�ΰ����� �߰�

//==============================================================================================================//

#include"good.h"
#include"AI.h"
#include"Environment.h"
#pragma warning(disable:4996)
#define SIZE 19
#define BLACK 1
#define WHITE 2

extern int flag;

//==============================================================================================================//

int main()
{
	Environment env_(SIZE);
	AI ai_(SIZE);
	system("mode con:cols=200 lines=50");
	system("title MyOmok");
	setcursortype(NOCURSOR);
	randomize();
	while(true)
	{
		env_.Init();

		while (true)
		{
			env_.draw_board();						// UI�� �̻��ϰ� ���ϰ�� draw_board2�� ���
			//draw_board2();

			env_.who_win();
			if (env_.win != 0)
				break;
			if (flag == BLACK)
			{
				env_.draw_dol();					// �ΰ����� vs ���
				env_.move_dol();
				env_.erase_dol();

				//ai_.get_action();				// �ΰ�����vs�ΰ�����
			}

			else if (flag == WHITE)
				ai_.get_action();
		}
		clrscr();
	}
	env_.print_win();
	system("pause");
}