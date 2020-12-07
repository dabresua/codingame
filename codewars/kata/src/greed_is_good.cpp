#include <cassert>
#include <iostream>

#include <vector>

/*
Three 1's => 1000 points
 Three 6's =>  600 points
 Three 5's =>  500 points
 Three 4's =>  400 points
 Three 3's =>  300 points
 Three 2's =>  200 points
 One   1   =>  100 points
 One   5   =>   50 point
*/

int score(const std::vector<int>& dice) {
	unsigned short count[6] = {0,0,0,0,0,0};
	for (int d : dice) {
		count[d-1]++;
	}
	unsigned int score3[6] = {1000,200,300,400,500,600};
	unsigned int score1[6] = {100,0,0,0,50,0};
	int score = 0;
	for (short i = 0; i < 6; i++) {
		std::cout << count[i] << " ";
		if (count[i] >= 3) {
			score+=score3[i];
			count[i]-=3;
		}
		score += count[i] * score1[i];
	}
	return score;
}

int main()
{
	assert(score({2, 3, 4, 6, 2}) == (0));
	assert(score({2, 4, 4, 5, 4}) == (450));

	return 0;
};
