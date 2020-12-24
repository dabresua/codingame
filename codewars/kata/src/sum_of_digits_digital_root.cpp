#include <cassert>
#include <iostream>

/* ----------------------- Recursive version -------------------------------- */
#if 0
int sum (int n)
{
	return n > 9 ? sum(n/10) + n%10: n%10;
}

int digital_root(int n)
{
	while (n >= 10) {
		n = sum(n);
	}
	return n;
}
#endif /* 0 */

/* ----------------------- Iterative version -------------------------------- */
int digital_root(int n)
{
	while (n >= 10) {
		int a = n;
		n = 0;
		while (a > 0) {
			n += a%10;
			a /= 10;
		}
	}
	return n;
}

/* ------------------------------ */
int main(void)
{
	assert(digital_root(16) == (7));
	assert(digital_root(195) == (6));
	assert(digital_root(992) == (2));
	assert(digital_root(167346) == (9));
	assert(digital_root(0) == (0));
	return 0;
}
