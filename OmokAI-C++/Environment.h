#pragma once

class Environment
{
public:
	int px;
	int py;
	int win;						// win이 1이면 흑돌 승, 2면 백돌 승
	int size_;

public:
	Environment(int);
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
};