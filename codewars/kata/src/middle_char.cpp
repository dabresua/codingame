#include <cassert>
#include <iostream>
#include <string>
#include <sstream>

std::string get_middle(std::string input)
{
	size_t len = input.length();
	return len%2 ? input.substr(len/2, 1) : input.substr(len/2-1, 2);
}

int main()
{
	#define TEST_LEN 2
	std::string test_vector[TEST_LEN] = {"test", "testing"};
	std::string test_results[TEST_LEN] = {"es","t"};

	for (size_t i = 0; i < TEST_LEN; i++) {
		std::string res = get_middle(test_vector[i]);
		std::cout << res << std::endl;
		assert(test_results[i].compare(res) == 0);
	}
	return 0;
};
