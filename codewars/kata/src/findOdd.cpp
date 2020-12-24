#include <iostream>

#include <cassert>
#include <vector>
#include <algorithm>

int findOdd(const std::vector<int>& numbers){
	int index = 0;
	while (index < numbers.size()) {
		int ret = numbers[index];
		if (std::count(numbers.begin(), numbers.end(), ret) % 2)
			return ret;
		index++;
	}
	assert(false); //Non-compatible set of numbers
	return 0;
}

using V = std::vector<int>;

int main()
{
	assert(findOdd(V{20,1,-1,2,-2,3,3,5,5,1,2,4,20,4,-1,-2,5}) == 5);
	assert(findOdd(V{1,1,2,-2,5,2,4,4,-1,-2,5}) == -1);
	assert(findOdd(V{20,1,1,2,2,3,3,5,5,4,20,4,5}) == 5);
	assert(findOdd(V{10}) == 10);
	assert(findOdd(V{1,1,1,1,1,1,10,1,1,1,1}) == 10);

	return 0;
};
