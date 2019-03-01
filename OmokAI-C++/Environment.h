#pragma once

class Environment
{
public:
	int px;
	int py;
	int win;						// win�� 1�̸� �浹 ��, 2�� �鵹 ��
	int size_;

public:
	Environment(int);
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
};