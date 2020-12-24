#include <cassert>
#include <iostream>
#include <vector>

std::vector<int> tribonacci(std::vector<int> signature, int n)
{
	if (n < 3) {
		signature.resize(n);
	}
	for (unsigned i = 3; i < n; i++) {
		signature.push_back(signature[i-3] + signature[i-2] + signature[i-1]);
	}
	return signature;
}

typedef struct test_vector_t {
	std::vector<int> signature;
	std::vector<int> expected;
} test_vector_t;

int main(void)
{
	const test_vector_t trib_test[] = {
		{
		.signature = { 1, 1, 1 },
		.expected = { 1, 1, 1, 3, 5, 9, 17, 31, 57, 105 },
		},
		{
		.signature = { 0, 0, 1 },
		.expected = { 0,0,1,1,2,4,7,13,24,44 },
		},
		{
		.signature = { 0, 1, 1 },
		.expected = { 0,1,1,2,4,7,13,24,44,81 },
		},
		{
		.signature = { 1, 0,  0 },
		.expected = { 1, 0, 0, 1, 1, 2, 4, 7, 13, 24 },
		},
		{
		.signature = { 1,2,3 },
		.expected = { 1,2,3,6,11,20,37,68,125,230 },
		},
		{
		.signature = { 1,2,3 },
		.expected = { 1,2 },
		},
		{
		.signature = { 1,2,3 },
		.expected = {},
		},
	};

	for (unsigned int i = 0; i < sizeof(trib_test)/sizeof(trib_test[0]); i++) {
		assert(tribonacci(trib_test[i].signature, trib_test[i].expected.size())
		       == trib_test[i].expected);
	}
}
