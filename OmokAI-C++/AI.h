#pragma once

// ���� �ΰ����� �Լ���

class AI
{
public:
	int size;
	double **value;				// ��ġ�Լ�
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