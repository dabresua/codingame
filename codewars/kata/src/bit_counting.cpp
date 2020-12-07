#include <cassert>
#include <iostream>

unsigned int countBits(unsigned long long n){
	unsigned int nones=0;
	unsigned long long pow2 = 1;
	while (n>0) {
		if ((n & pow2) == pow2) {
			nones++;
			n-=pow2;
		}
		pow2*=2;
	}
	return nones;
}

int main()
{
	assert(countBits(0) == (0));
	assert(countBits(4) == (1));
	assert(countBits(7) == (3));
	assert(countBits(9) == (2));
	assert(countBits(10) == (2));
	assert(countBits(26) == (3));
	assert(countBits(77231418) == (14));
	assert(countBits(12525589) == (11));
	assert(countBits(3811) == (8));
	assert(countBits(392902058) == (17));

	return 0;
};
