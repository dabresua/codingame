#include <cassert>
#include <iostream>
#include <math.h>

bool is_square(int n)
{
	return !fmod(sqrt(n),1);
}

int main()
{
	#define TEST_LEN 6
	int test_vector[TEST_LEN] = {-1,0,3,4,25,26};
	bool test_results[TEST_LEN] = {false,true,false,true,true,false};

	for (size_t i = 0; i < TEST_LEN; i++) {
		assert(test_results[i] == is_square(test_vector[i]));
	}
	return 0;
};
