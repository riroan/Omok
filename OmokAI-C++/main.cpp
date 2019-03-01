// OMOK GAME
//==============================================================================================================//
// 2018-04-07
// ver 1.0
// 단순한 인공지능 탑재
// 현재 오목판을 분석하여 가치함수를 설정함
// 가치함수중에서 가장 큰 값을 가지는 위치에 착수함
// 가치함수의 최댓값이 여러개일경우 랜덤한 곳에 착수함
// 모니터에 따라 UI가 이상하게 보일수 있음 -> main 함수에 있는 draw_board2() 사용

// 2018-04-08
// ver 1.1
// 가치함수에서 범위가 벗어나면 에러나는 점을 수정함
// c++버전 추가
// 인공지능vs인공지능 추가

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
			env_.draw_board();						// UI가 이상하게 보일경우 draw_board2를 사용
			//draw_board2();

			env_.who_win();
			if (env_.win != 0)
				break;
			if (flag == BLACK)
			{
				env_.draw_dol();					// 인공지능 vs 사람
				env_.move_dol();
				env_.erase_dol();

				//ai_.get_action();				// 인공지능vs인공지능
			}

			else if (flag == WHITE)
				ai_.get_action();
		}
		clrscr();
	}
	env_.print_win();
	system("pause");
}