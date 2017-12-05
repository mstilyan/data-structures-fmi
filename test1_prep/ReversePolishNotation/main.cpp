#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <sstream>

using namespace std;

template <typename T>
T lexicalCast(const std::string& s)
{
	std::stringstream ss(s);

	T result;
	if ((ss >> result).fail() || !(ss >> std::ws).eof())
	{
		throw std::bad_cast();
	}

	return result;
}

void executeBinaryOperation(stack<int>& machine, char operation)
{
	int n2 = machine.top();
	machine.pop();
	int n1 = machine.top();
	machine.pop();

	switch (operation)
	{
	case 'x':
		machine.push(n1 * n1 + n2);
		break;
	case '+':
		machine.push(n1 + n2);
		break;
	case '-':
		machine.push(n1 - n2);
		break;
	case '*':
		machine.push(n1 * n2);
		break;
	case '/':
		machine.push(n1 / n2);
		break;
	}
}

void executeUnaryOperation(stack<int>& machine, char operation)
{
	int n1 = machine.top();
	machine.pop();

	machine.push(n1 * 2 + 1);
}

void executeTernaryOperation(stack<int>& machine, char operation)
{
	int n3 = machine.top();
	machine.pop();
	int n2 = machine.top();
	machine.pop();
	int n1 = machine.top();
	machine.pop();

	machine.push(n1 + n2 * 2 + n3 * 3);
}

int evaluateExpression(const vector<string>& expression)
{
	stack<int> machine;

	for (string token : expression)
	{
		if (token == "y") //process unary operation
		{
			switch (machine.empty())
			{
			case true:
				throw invalid_argument("Invalid expression!");
			default:
				char operation = token[0];
				executeUnaryOperation(machine, operation);
			}
		}
		else if (token == "+" || token == "-" || token == "*" || token == "/" || token == "x") //process binary operation
		{
			switch (machine.size())
			{
			case 0:
			case 1:
				throw invalid_argument("Invalid expression!");
			default:
				char operation = token[0];
				executeBinaryOperation(machine, operation);
			}
		}
		else if (token == "z") //process ternary operation
		{
			switch (machine.size())
			{
			case 0:
			case 1:
			case 2:
				throw invalid_argument("Invalid expression!");
			default:
				char operation = token[0];
				executeTernaryOperation(machine, operation);
			}
		}
		else //token should be operand if not operation
		{
			try
			{
				int operand = lexicalCast<int>(token);
				machine.push(operand);
			}
			catch (...)
			{
				throw invalid_argument("Invalid expression!");
			}
		}
	}

	if (machine.empty())
	{
		throw invalid_argument("Invalid expression!");
	}

	return machine.top();
}

vector<string> stringSplit(string& s)
{
	vector<string> result;
	stringstream ss(s);
	string expression;

	while (ss >> expression)
	{
		result.push_back(expression);
	}

	return result;
}

int main(int argc, char* argv[])
{
	int num;
	cin >> num;
	cin.ignore();

	for (int i = 0; i < num; ++i)
	{
		string input;
		getline(cin, input);

		try
		{
			cout << evaluateExpression(stringSplit(input)) << endl;
		}
		catch (...) //Input Expression is invalid!
		{
			cout << "NO" << endl;
		}
	}


	return 0;
}
