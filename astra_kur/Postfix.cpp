#include "Postfix.h"
double pi = 3.14159265358979323846;
double e = 2.71828182845904523536;

Postfix::Postfix() {
	stack = new Stack();
	postfix_string = new List();
}

Postfix::~Postfix() {
	postfix_string->~List();
	stack->~Stack();
	
}

bool Postfix::is_number(char in_symbol) {
	string numbers = {"1234567890."};
	int i = 0;
	for (char current_number : numbers) {
		if (current_number == in_symbol) return true;
		
	}
	return false;
}

bool Postfix::is_function(char in_symbol) {
	string symbols = { "sincolgntqrabepi"};
	int i = 0;
	for (char current_symbol : symbols) {
		if (current_symbol == in_symbol) return true;
		
	}
	return false;
}

int Postfix::which_operator(char in_symbol) {
	if (in_symbol == '+' || in_symbol == '-') return add_sub;
	else
		if (in_symbol == '*' || in_symbol == '/') return multipl_division;
		else 
			if (in_symbol == '(') return left_brecket;
			else
				if (in_symbol == ')' ) return right_brecket;
				else 
					if (in_symbol == '^') return degree;
					else return not_operator;
}

double Postfix::operator_result(char in_symbol, double operand_1, double operand_2) {
	double result = 0;
	switch (in_symbol) {
	case '+':
		result = operand_1 + operand_2;
		break;
	case '-':
		result = operand_1 - operand_2;
		break;
	case '*':
		result = operand_1 * operand_2;
		break;
	case '/':
		result = operand_1 / operand_2;
		break;
	case '^':
		result = pow(operand_1 ,operand_2);
		break;
	}
	return result;
}

int Postfix::which_function(string function) {
	if (function == "cos") return Cos;
	else
		if (function == "sin") return Sin;
		else
			if (function == "tg") return Tg;
			else
				if (function == "ctg") return Ctg;
				else
					if (function == "log") return Log;
					else
						if (function == "ln") return Ln;
						else
							if (function == "sqrt") return Sqrt;
							else
								if (function == "abs") return Abs;
								else
									if (function == "exp") return Exp;
									else
										if (function == "pi") return Pi;
										else
											if (function == "e") return E;
											else return not_operator;
}

double Postfix::function_result(int func, double argument) {
	double result = 0;
	switch (func) {
	case Cos:
		result = cos(argument);
		break;
	case Sin:
		result = sin(argument);
		break;
	case Tg:
		result = tan(argument);
		break;
	case Ctg:
		result = 1/(tan(argument));
		break;
	case Log:
		result = log10(argument);
		break;
	case Ln:
		result = log(argument);
		break;
	case Sqrt:
		result = sqrt(argument);
		break;
	case Abs:
		result = abs(argument);
		break;
	case Exp:
		result = exp(argument);
		break;
	}
	return result;
}

void Postfix::to_Postfix(string input) {
	size_t i = 0, left_breckets = 0, right_breckets = 0, count_dots = 0;
	string cur_postfix_elem ;
	while (i < input.size()) {
		cur_postfix_elem.clear();
		if (input[i]=='-' && postfix_string->isEmpty()) {
			cur_postfix_elem.push_back('0');
			postfix_string->push_back(cur_postfix_elem, not_operator);
			cur_postfix_elem.clear();
			stack->push(input[i++], add_sub);
		}
		if (input[i] == ' ') //skip spaces
			i++;
		if (is_number(input[i])) {	//input numbers
			count_dots = 0;
			while (is_number(input[i])) {
				if (input[i] == '.') 
					count_dots++;
				cur_postfix_elem.push_back(input[i++]);
			}
			if (count_dots>1)
				throw ("Invalid input. Too many dots in one number, don't you think?");
			if (input[i] == ' ') //skip spaces
				i++;
			if (input[i] == '(') {
				throw ("Invalid input. Number before brecket without operator.");
			}
			postfix_string->push_back(cur_postfix_elem, not_operator);
			cur_postfix_elem.clear();
		}
		if (which_operator(input[i]) == left_brecket ) { //input left brecket into stack
			left_breckets++;
			stack->push(input[i++], left_brecket);
			if (which_operator(input[i]) == right_brecket)
				throw ("Invalid input. Expression like () was not expected.");
			if (input[i] == '-') {
				cur_postfix_elem.push_back('0');
				postfix_string->push_back(cur_postfix_elem, not_operator);
				cur_postfix_elem.clear();
				stack->push(input[i++], add_sub);
			}
		}
		else {
			//учесть случай () ?
			if (which_operator(input[i]) == right_brecket) {
				right_breckets++;
				if (right_breckets > left_breckets)
					throw ("Invalid input. Left bracket required.");
				while (!stack->isEmpty() && (stack->getTop()->priority != left_brecket))  //outputing into prefix string operators while don't get left bracket, exterminate right and left breckets
					postfix_string->push_back(stack->pop());
				stack->pop();
				i++;
			}
			else {

				if (which_operator(input[i]) != not_operator) {
					if (stack->isEmpty())
						stack->push(input[i], which_operator(input[i]));
					else
						if (!stack->isEmpty() && stack->getTop()->priority < which_operator(input[i]))
							stack->push(input[i], which_operator(input[i]));
						else
							if (!stack->isEmpty() && stack->getTop()->priority >= which_operator(input[i])) { //outputing into prefix string operators while don't get operator whith lower priority
								while (!stack->isEmpty() && (stack->getTop()->priority >= which_operator(input[i])))
									postfix_string->push_back(stack->pop());
								stack->push(input[i], which_operator(input[i]));
							}
					i++;
				}
				if (is_function(input[i])) { //input function
					string function;
					while (is_function(input[i]))
						function.push_back(input[i++]);
					if (which_function(function) != not_operator) {
						if (stack->isEmpty())
							stack->push(function, func);
						else
							if (!stack->isEmpty() && (stack->getTop()->priority < func))
								stack->push(function, func);
							else
								if (!stack->isEmpty() && stack->getTop()->priority >= func) {
									while (!stack->isEmpty() && (stack->getTop()->priority >= func))
										postfix_string->push_back(stack->pop());
									stack->push(function, func);
								}
						if (input[i] == ' ') //skip spaces
							i++;
						if (which_operator(input[i]) == left_brecket) {
							left_breckets++;
							stack->push(input[i++], left_brecket);
							if (input[i] == '-') {
								cur_postfix_elem.push_back('0');
								postfix_string->push_back(cur_postfix_elem, not_operator);
								cur_postfix_elem.clear();
								stack->push(input[i++], add_sub);
							}
							if (is_number(input[i])) {
								count_dots = 0;
								while (is_number(input[i])) {
									if (input[i] == '.')
										count_dots++;
									cur_postfix_elem.push_back(input[i++]);
								}
								if (count_dots > 1)
									throw ("Invalid input. Too many dots in one number, don't you think?");
								if (input[i] == ' ') //skip spaces
									i++;
								if (input[i] == '(') {
									throw ("Invalid input. Number before brecket without operator.");
								}
								postfix_string->push_back(cur_postfix_elem, not_operator); //did i broke it...
								cur_postfix_elem.clear();
							}
						}
						if (which_operator(input[i]) == right_brecket) {
							right_breckets++;
							if (right_breckets > left_breckets)
								throw ("Invalid input. Left bracket required.");

							while (stack->getTop()->priority != left_brecket)
								postfix_string->push_back(stack->pop());
							stack->pop();
							i++;

						}

					}
					//else
						//throw ("Wrong function");
				}
			}
		}
		if (input[i] == ' ') //skip spaces
			i++;
		if (i == input.size()) break;
		if (!is_number(input[i]) && !is_function(input[i]) && which_operator(input[i])== not_operator) {
			throw ("Invalid input. Wrong symbols.");
			break;
		}
	}
	if (!stack->isEmpty()) {
		while (!stack->isEmpty()) {
			postfix_string->push_back(stack->pop());
		}
	}
	if (left_breckets!=right_breckets)
		throw ("Invalid input. Wrong number of breckets.");
}

double  Postfix::calculation() {
	Node* current = postfix_string->set_head();
	double operand_1=0, operand_2=0, result = 0;
	//size_t number_count = 0, operator_count = 0;
	string number;
	number.clear();
	stack = new Stack();
	while (current != nullptr) {
		if (is_number(current->data[0])) {
			stack->push(current->data, not_operator);
		}
		if (which_function(current->data)==Pi) {
			stack->push(current);
		}
		if (which_function(current->data) == E) {
			stack->push(current);
		}
		if (which_operator(current->data[0]) != not_operator) {
			number.clear();
			if (!stack->isEmpty()) {
				number = stack->pop()->data;
				if (which_function(number) == Pi) operand_2 = pi;
				else if (which_function(number) == E) operand_2 = e;
					else operand_2 = stod(number);
				number.clear();
			}
			else throw("Invalid input. Too much operators.");
			if (!stack->isEmpty()) {
				number = stack->pop()->data;
				if (which_function(number) == Pi) operand_1 = pi;
				else if (which_function(number) == E) operand_1 = e;
				else operand_1 = stod(number);
				number.clear();
			}
			else throw("Invalid input. Too much operators.");
			result = operator_result(current->data[0],operand_1,operand_2);
			stack->push(to_string(result),not_operator);
		}
		if (which_function(current->data) != not_operator && which_function(current->data) != Pi && which_function(current->data) != E) {
			number.clear();
			if (!stack->isEmpty()) {
				number = stack->pop()->data;
				if (which_function(number) == Pi) operand_1 = pi;
				else if (which_function(number) == E) operand_1 = e;
				else operand_1 = stod(number);
				number.clear();
			}
			else throw("Invalid input. Too much operators.");
			result = function_result(which_function(current->data),operand_1);
			stack->push(to_string(result), not_operator);
		}
		
		current = current->next;
	}
	if (!stack->isEmpty() && result==0) {
		result = stod(stack->pop()->data);
	}
	return result;
}

void Postfix::out() {
	postfix_string->print_to_console();
}