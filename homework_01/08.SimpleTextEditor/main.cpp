#include <iostream>
#include <string>
#include <stack>
#include <array>

using namespace std;

class TextEditor
{
	stack<array<string, 2>> operationsHistory;
	string content;

public:
	void append(string& strToAppend)
	{
		content.append(strToAppend);
		operationsHistory.push({ "delete", std::to_string(strToAppend.length()) });
	}
	void remove(int count)
	{
		auto erasedString = content.substr(content.size() - count);
		content.erase(content.size() - count);
		operationsHistory.push({ "append", erasedString });
	}
	void print(int nth) const
	{
		cout << content[nth - 1] << endl;
	}
	void undo ()
	{
		array<string, 2> reverseOperation = operationsHistory.top();
		operationsHistory.pop();

		if (reverseOperation[0] == "append")
			content.append(reverseOperation[1]);
		else
			content.erase(content.size() - stoi(reverseOperation[1]));
	}
	void print() const
	{
		cout << content << endl;
	}
};

int main(int argc, char* argv[])
{
	TextEditor textEditor;
	
	int queriesCount;
	cin >> queriesCount;

	for (int i = 0; i < queriesCount; ++i)
	{
		int command;
		cin >> command;

		string appendString;
		int endOffset;
		int nth;
		
		switch (command)
		{
		case 1:
			cin >> appendString;
			textEditor.append(appendString);
			break;
		case 2:
			cin >> endOffset;
			textEditor.remove(endOffset);
			break;
		case 3:
			cin >> nth;
			textEditor.print(nth);
			break;
		case 4:
			textEditor.undo();
			break;
		}
	}

	return 0;
}
