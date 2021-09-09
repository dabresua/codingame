#include <iostream>
#include <thread>

#define MAX_THREADS (5)

using namespace std;

void printHello(int N)
{
	cout << "Hello. I'm the thread " << N << endl;
}

int main()
{
	printHello(7);
	/*
	thread ths[MAX_THREADS];
	for (int i = 0; i < MAX_THREADS; i++)
		ths[i] = thread(printHello, i);

	for (int i = 0; i < MAX_THREADS; i++)
		ths[i].join();
	*/
	return 0;
}
