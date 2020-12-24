#include <iostream>
#include <cassert>

#include <vector>

class Decomp
{
public:
	static std::vector<long long> decompose(long long n);
private:
	static std::vector<long long> dec2(long long n, long long left);
};

static std::vector<long long> dec2(long long n, long long left)
{
	std::vector<long long> ret;
	if (n < 1)
		return ret;
	long long acu = 0;
	while (left - acu > 0 && n > 0) {
		long long act = (acu + n*n);
		if (left > act) {
			std::vector<long long> tmp = dec2(n-1, left-act);
			if (tmp.size()) {
				ret.insert(ret.begin(), n);
				ret.insert(ret.begin(),tmp.begin(),tmp.end());
				return ret;
			}
		} else if (left == act) {
			ret.insert(ret.begin(), n);
			return ret;
		}
		n--;
	}
	if (left - acu)
		ret.clear();
	return ret;
}

static std::vector<long long> decompose(long long n)
{
	std::vector<long long> ret = dec2(n-1, n*n);
	return ret;
}

typedef struct tect_vector_t {
	int in;
	std::vector<long long> out;
} tect_vector_t;

int main()
{
	tect_vector_t test_vectors[] = {
		{.in = 2, .out = {}},
		{.in = 5, .out = {3,4}},
		{.in = 7, .out = {2,3,6}},
		{.in = 6, .out = {}},
		{.in = 50, .out = {1,3,5,8,49}},
		{.in = 44, .out = {2,3,5,7,43}},
	};
	for (auto test : test_vectors) {
		std::cout << "TEST VECTOR in " << test.in << " out {";
		for (auto a : test.out) {
			std::cout << a << " ";
		}
		std::cout << "}" << std::endl;
		assert(decompose(test.in) == test.out);
		std::cout << std::endl;
	}
}
