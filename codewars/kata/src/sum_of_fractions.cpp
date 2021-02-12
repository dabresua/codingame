#include <iostream>
#include <cassert>

#include <utility>
#include <vector>

#include <utility>

/* Published code */
#if 0
#include <utility>

class SumFractions
{
public:
	static std::pair <int, int> sumFracts(std::vector<std::vector<int>> &l)
	{
		int nom = 0, den = 1, max_den = 1;
		for (auto f : l) {
			den *= f[1];
			if (f[1] > max_den)
				max_den = f[1];
		}
		for (auto f : l)
			nom += f[0]*den/f[1];
		for (int i = 2; i <= max_den; i++) {
			if (!(den % i) && !(nom % i)) {
				den = den / i;
				nom = nom / i;
				i--;
			}
		}
		return {nom, den};
	}
};
#endif /* 0 */


static std::pair <int, int> sumFracts(std::vector<std::vector<int>> &l)
{
	int nom = 0, den = 1, max_den = 1;
	for (auto f : l) {
		den *= f[1];
		if (f[1] > max_den)
			max_den = f[1];
	}
	for (auto f : l)
		nom += f[0]*den/f[1];
	std::cout << nom << " / " << den << " max " << max_den << std::endl;
	for (int i = 2; i <= max_den; i++) {
		if (!(den % i) && !(nom % i)) {
			den = den / i;
			nom = nom / i;
			std::cout << "divisible by " << i << ": "<< nom << " / " << den << std::endl;
			i--;
		}
	}
	std::cout << nom << " / " << den << std::endl;
	return {nom, den};
}


int main()
{
	std::vector<std::vector<int>> a1 = { {1,2}, {2,9}, {3,18}, {4,24}, {6,48} };
	std::pair<int, int> r1 = {85, 72};
	assert(sumFracts(a1) == r1);
	std::vector<std::vector<int>> a2 = { {1, 2}, {1, 3}, {1, 4} };
	std::pair<int, int> r2 = {13, 12};
	assert(sumFracts(a2) == r2);
	std::vector<std::vector<int>> a3 = { {1, 3}, {5, 3} };
	std::pair<int, int> r3 = {2, 1};
	assert(sumFracts(a3) == r3);
	std::vector<std::vector<int>> a4 = { };
	std::pair<int, int> r4 = {0, 1};
	assert(sumFracts(a4) == r4);
	return 0;
};
