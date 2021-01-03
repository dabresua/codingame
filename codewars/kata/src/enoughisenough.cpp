#include <iostream>

#include <cassert>
#include <vector>
#include <algorithm>

std::vector<int> deleteNth(std::vector<int> arr, int n)
{
	std::vector<int> ret;
	for (int ni : arr) {
		unsigned int count = 0;
		for (int nj : ret) {
			if (nj == ni)
				count++;
		}
		if (count < n)
			ret.push_back(ni);
	}
	return ret;
}

using V = std::vector<int>;

int main()
{
	assert(deleteNth({20,37,20,21}, 1) == (std::vector<int>({20, 37, 21})));
	assert(deleteNth({1,1,3,3,7,2,2,2,2}, 3) == (std::vector<int>({1, 1, 3, 3, 7, 2, 2, 2})));

	return 0;
};
