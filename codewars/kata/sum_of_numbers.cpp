#include <cassert>
#include <iostream>
#include <math.h>

int get_sum(int a, int b)
{
	int r = (a < b) ? b : a;
	for (int i = ((a < b) ? a : b); i < ((a < b) ? b : a); i++) {
		r+=i;
	}
	return r;
}

int main()
{
	assert(get_sum(0,-1) == -1);
	assert(get_sum(0, 1) == 1);

	return 0;
};
