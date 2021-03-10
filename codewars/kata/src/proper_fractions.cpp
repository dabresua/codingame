#include <iostream>
#include <cassert>

long properFractions(long den)
{
	long ret = 0;



	for (long i = 1; i < den; i++) {
		bool divisible = false;
		for (long j = 2; j <= i; j++) {
			if (!(i % j) && !(den % j)) {
				divisible = true;
				break;
			}
		}
		if (!divisible) {
			//std::cout << i << " / " << den << std::endl;
			ret++;
		}
	}
	//std::cout << "ret " << ret << std::endl;
	return ret;
}

int main()
{
	assert(properFractions(1) == (0));
	assert(properFractions(2) == (1));
	assert(properFractions(5) == (4));
	assert(properFractions(15) == (8));
	assert(properFractions(25) == (20));
	return 0;
};
