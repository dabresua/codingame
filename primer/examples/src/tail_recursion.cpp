/**
 * @file tail_recursion.cpp
 * @brief tail recursion example
 */
#include <iostream>

using namespace std;

int fibo_ite(int n)
{
	if (n == 0)
		return 0;
	int n0 = 0, n1 = 1;
	for (int i = 2; i <= n; i++) {
		int tmp = n1;
		n1 = n1 + n0;
		n0 = tmp;
	}
	return n1;
}

int fibo_rec(int n, bool debug = false)
{
	if (debug) {
		cout << "fibo_rec " << n << endl;
	}
	if (n == 1)
		return 1;
	else if (n == 0)
		return 0;
	else
		return fibo_rec(n-1, debug) + fibo_rec(n-2, debug);
}

int fibo_tail(int n, int a = 0, int b = 1, bool debug = false)
{
	if (debug) {
		cout << "fibo_tail " << n << endl;
	}
	if (n == 1)
		return b;
	else if (n == 0)
		return a;
	else
		return fibo_tail(n-1, b, a+b, debug);
}

int main ()
{
	string line = string(80, '-');
	cout << line << endl;
	cout << "fibo iterative" << endl;
	cout << line << endl;
	for (int i = 0; i < 20; i++) {
		cout << i << ":\t"<< fibo_ite(i) << endl;;
	}

	cout << line << endl;
	cout << "fibo recursive" << endl;
	cout << line << endl;
	for (int i = 0; i < 20; i++) {
		cout << i << ":\t"<< fibo_rec(i) << endl;;
	}

	cout << line << endl;
	cout << "fibo tail recursive" << endl;
	cout << line << endl;
	for (int i = 0; i < 20; i++) {
		cout << i << ":\t"<< fibo_tail(i) << endl;;
	}

	cout << line << endl;
	cout << "debugging fibo recursive" << endl;
	cout << line << endl;
	fibo_rec(5, true);

	cout << line << endl;
	cout << "debugging fibo tail recursive" << endl;
	cout << line << endl;
	fibo_tail(5, 0, 1, true);

	return 0;
}
