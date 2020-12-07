#include <cassert>
#include <iostream>
#include <string>
#include <sstream>

std::string multi_table(int number)
{
	std::ostringstream os;
	for (int i = 1; i <= 10; i++) {
		os << i << " * " << number << " = " << i*number << (i<10 ? "\n" : "");
	}
	return os.str();
}

int main()
{
	std::string res;

	#define TEST_LEN 2
	int test_vector[TEST_LEN] = {5,1};
	std::string test_results[TEST_LEN] = {
		"1 * 5 = 5\n2 * 5 = 10\n3 * 5 = 15\n4 * 5 = 20\n5 * 5 = 25\n6 * 5 = 30\n7 * 5 = 35\n8 * 5 = 40\n9 * 5 = 45\n10 * 5 = 50",
		"1 * 1 = 1\n2 * 1 = 2\n3 * 1 = 3\n4 * 1 = 4\n5 * 1 = 5\n6 * 1 = 6\n7 * 1 = 7\n8 * 1 = 8\n9 * 1 = 9\n10 * 1 = 10",
	};

	for (size_t i = 0; i < TEST_LEN; i++) {
		assert(test_results[i].compare(multi_table(test_vector[i])) == 0);
	}
	return 0;
};
