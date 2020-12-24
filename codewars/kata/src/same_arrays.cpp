#include <cassert>
#include <iostream>

#include <vector>
#include <algorithm>

static bool cmp_abs(int a, int b)
{
	return abs(a) < abs(b);
}

static bool comp(std::vector<int>&a, std::vector<int>&b)
{
	if (a.size() != b.size())
		return false;
	std::sort(a.begin(), a.end(), cmp_abs);
	std::sort(b.begin(), b.end(), cmp_abs);
	for (unsigned int i = 0; i < a.size(); i++) {
		//std::cout << "a: " << a[i]*a[i] << " == " << b[i] << std::endl;
		if (a[i]*a[i] != b[i])
			return false;
	}
	return true;
}

int main(void)
{
	std::vector<int> a = {121, 144, 19, 161, 19, 144, 19, 11};
	std::vector<int> b = {14641, 20736, 361, 25921, 361, 20736, 361, 121};
	//assert(comp(a,b) == true);
	//a = {121, 144, 19, 161, 19, 144, 19, 11};
	//b = {14641, 20736, 361, 25921, 361, 20736, 362, 121};
	//assert(comp(a,b) == false);

	a = {11,19,19,19,121,144,144,161,11,19,19,19,11,19,19,19,-121};
	b = {121,361,361,361,14641,20736,20736,25921,121,361,361,362,121,361,361,362,121};
	assert(comp(a,b) == true);

	return 0;
}
