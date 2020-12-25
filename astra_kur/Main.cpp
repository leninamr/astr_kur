#include "Postfix.h"

int main() {
	Postfix* postfix;
	double result;
	string input;
	cout << "For escape write exit, enter the negative exponent in breckets:"<<endl;
	
	//postfix = new Postfix();
	//string input2 = { "pi" };
	//postfix->to_Postfix(input2);
	//cout << postfix->calculation();
	while (1) {
		postfix = new Postfix();
		cout << "Enter expression:" << endl;
		getline(cin, input);
		if (input == "exit") 
			break;
		try {
			postfix->to_Postfix(input);
			cout << "Postfix form:" << endl;
			postfix->out();
			result = postfix->calculation();
			cout << "Result:" << endl;
			cout << result << endl;
		}
		catch (const char* error) {
			cout << error << endl;
		}
	}
	return 0;
}