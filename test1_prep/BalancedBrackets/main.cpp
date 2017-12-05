#include <iostream>
#include <string>
#include <stack>

using namespace std;

bool validateExpression(const string& input)
{
	stack<int> brackets;
	for (char el : input)
	{
		if (el == '(' || el == '[' || el == '{')
		{
			brackets.push(el);
		}
		else if (el == ')' || el == ']' || el == '}')
		{
			if (brackets.size() == 0)
				return false;

			char bracket = brackets.top();
			brackets.pop();

			if (bracket == '(' && el == ')')
				continue;
			if (bracket == '[' && el == ']')
				continue;
			if (bracket == '{' && el == '}')
				continue;

			return false;
		}
	}

	return brackets.empty();
}

int main(int argc, char* argv[])
{
	int expressionsCount;
	string input;

	cin >> expressionsCount;
	cin.ignore();

	for (int i = 0; i < expressionsCount; ++i)
	{
		getline(cin, input);
		cout << (validateExpression(input) ? "YES" : "NO") << endl;
	}

	return 0;
}
