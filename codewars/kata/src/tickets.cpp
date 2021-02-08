#include <iostream>
#include <cassert>

#include <string>
#include <vector>
#include <algorithm>

std::string tickets(const std::vector<int>& peopleInLine) {
	int bills[2] = {0,0};
	for (auto person : peopleInLine) {
		switch (person) {
		case 25: bills[0]++; break;
		case 50: bills[0]--; bills[1]++; break;
		case 100:
			if (bills[1] > 0) {
				bills[1]--;
				bills[0]--;
			} else {
				bills[0]-=3;
			}
			break;
		default: assert(false);
		}
		if (bills[0] < 0 || bills[1] < 0)
			return "NO";
	}
	return "YES";
}

int main()
{
	assert(tickets({25, 25, 50, 50}) == ("YES"));
	assert(tickets({25, 100}) == ("NO"));
	assert(tickets({25,25,25,25,50,100}) == ("YES"));
	assert(tickets({50,50,50,50,50,50,50,50,50,50}) == ("NO"));
	assert(tickets({25,50,100,25,25,25,50}) == ("NO"));

	return 0;
};
