#pragma once

// 오목 인공지능 함수들

class AI
{
public:
	int size;
	double **value;				// 가치함수
public:
	AI(int);
	~AI();
	void value_four();
	void value_three();
	void value_two();
	void value_one();
	void value_init();
	void get_action();
	void value_update();
	void print_value();
};