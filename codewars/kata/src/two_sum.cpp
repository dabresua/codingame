#include <iostream>
#include <cassert>

#include <vector>
#include <utility>

std::pair<std::size_t, std::size_t> two_sum(const std::vector<int>& numbers,
                                            int target) {
	for (unsigned int i = 0; i < numbers.size(); i++)
		for (unsigned int j = 0; j < numbers.size(); j++)
			if (i != j && numbers[i] + numbers[j] == target)
				return {i, j};
	return {0, 0};
}

int main()
{
	std::vector<int> input = {1, 2, 3};
	std::pair<std::size_t, std::size_t> res = {0, 2};
	assert(two_sum(input, 4) == res);

	input = {1234, 5678, 9012};
	res = {1, 2};
	assert(two_sum(input, 14690) == res);

	input = {2, 2, 3};
	res = {0, 1};
	assert(two_sum(input, 4) == res);
	return 0;
}
