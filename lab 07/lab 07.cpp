#include<iostream>
#include<string>
#include <stack>
using namespace std;

#pragma region Algorith to Convert Prefix to Postfix
// Read the Prefix expression in reverse order(from right to left)
// If the symbol is an operand, then push it onto the Stack
// If the symbol is an operator, then pop two operands from the Stack
// Create a string by concatenating the two operandsand the operator after them.
// string = operand1 + operand2 + operator
// And push the resultant string back to Stack
// Repeat the above steps until end of Prefix expression.
#pragma endregion

#pragma region Algorithm to Convert Postfix to Prefix
// Read the Postfix expression from left to right
// If the symbol is an operand, then push it onto the Stack
// If the symbol is an operator, then pop two operands from the Stack
// Create a string by concatenating the two operandsand the operator before them.
// string = operator + operand2 + operand1
// And push the resultant string back to Stack
// Repeat the above steps until end of Postfix expression.
#pragma endregion

bool isOperator(char x)
{
	switch (x) {
	case '+':
	case '-':
	case '/':
	case '*':
		return true;
	}
	return false;
}

string Pre_To_Post(string Pre)
{
	stack<string> s;
	for (int i = Pre.size(); i >= 0; i--)
	{
		//cheak if the symbol is operator 
		if (isOperator(Pre[i]))
		{
			//pop two operand from stack
			string op1 = s.top();
			s.pop();
			string op2 = s.top();
			s.pop();
			//concatinate to both oprand with operator 
			string temp = op1 + op2 + Pre[i];
			//push to stack
			s.push(temp);
		}
		
		else
		{
			s.push(string(1,Pre[i]));
		}
	}
	return s.top();
}
int main()
{
	string pre_exp;
	cin >> pre_exp;
	cout << Pre_To_Post(pre_exp);
	return 0;
}