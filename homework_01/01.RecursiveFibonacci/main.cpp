#include <iostream>

using namespace std;

long fib(unsigned int n, long prevFib = 1, long currFib = 1)
{
	if (n == 0) return 0;
	if (n == 1) return prevFib;

	return fib(n - 1, currFib, prevFib + currFib);
}

int main(int argc, char* argv[])
{
	cout << fib(11) << endl;
	return 0;
}
