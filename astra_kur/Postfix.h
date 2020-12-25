#pragma once
#include "Stack.h"
#include <stdexcept>
#include <cmath>
#include <string>

class Postfix {
private:
	Stack *stack;
	List *postfix_string;
	//int size_postfix = 0;
	enum functions {
		Sin,
		Cos,
		Log,
		Ln,
		Tg,
		Ctg,
		Sqrt,
		Abs,
		Exp,
		Pi,
		E
	};
	enum priorities {
		left_brecket,
		right_brecket,
		add_sub,
		multipl_division,
		degree,
		func,
		not_operator = -1
	};


public:
	Postfix();
	~Postfix();
	void to_Postfix(string input);
	double calculation();

	double operator_result(char in_symbol, double operand_1, double operand_2);
	double function_result(int func, double argument);
	int which_operator(char in_symbol);
	bool is_number(char in_symbol);
	bool is_function(char in_symbol);
	int which_function(string function);
	void out();
};

