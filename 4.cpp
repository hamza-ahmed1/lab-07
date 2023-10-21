#include<iostream>
#include<string>
using namespace std;
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
