#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstring>


using namespace std;

bool orderbymin(int a, int b)
{
	return a < b;
}

bool orderbyabs(int a, int b)
{
	return abs(a) < abs(b);
}

void print(const int* a)
{
	for (size_t i = 0; i < 10; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

int main()
{
	const int numbers[10] = {0, 7, -1, 3, 6, 5, 99, -103, -8, -4};
	int copy1[10];
	int copy2[10];
	memcpy(copy1, numbers, 10 * sizeof(int));
	memcpy(copy2, numbers, 10 * sizeof(int));

	cout << string(80, '-') << endl;
	cout << "classic" << endl;
	print(numbers);
	std::sort(copy1, copy1 + 10, orderbymin);
	print(copy1);
	std::sort(copy2, copy2 + 10, orderbyabs);
	print(copy2);

	cout << string(80, '-') << endl;
	memcpy(copy1, numbers, 10 * sizeof(int));
	memcpy(copy2, numbers, 10 * sizeof(int));
	print(copy1);
	print(copy2);

	cout << string(80, '-') << endl;
	cout << "lambda" << endl;
	print(numbers);
	std::sort(copy1, copy1 + 10,
	          // lambda expression
	          [](int a, int b) {
	            	return (a < b);
	          }
	);
	print(copy1);
	std::sort(copy2, copy2 + 10,
	          // lambda expression
	          [](int a, int b) {
	            	return (abs(a) < abs(b));
	          }
	);
	print(copy2);

	return 0;
}
