#include <iostream>
#include <stack>
#include <set>

using namespace std;

template<typename  T>
class MaxStack
{
private:
	stack<T> sck;
	multiset<T> set;
public:
	void add(T value)
	{
		sck.push(value);
		set.insert(value);
	}
	void remove()
	{
		T top = sck.top();
		sck.pop();

		auto itr = set.find(top);
		set.erase(itr);
	}
	T max()
	{
		return *--set.end();
	}
};

int main(int argc, char* argv[])
{
	long long count;
	cin >> count;
	MaxStack<long long> s;

	for (int i = 0; i < count; ++i)
	{
		int command;
		cin >> command;

		switch (command)
		{
		case 1:
			long long value;
			cin >> value;
			s.add(value);
			break;
		case 2:
			s.remove();
			break;
		case 3:
			cout << s.max() << endl;
		}
	}
}
