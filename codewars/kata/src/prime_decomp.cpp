#include <cassert>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

class PrimeDecomp
{
public:
	static std::vector<int>& nextPrime(std::vector<int> &primes);
	static std::string factors(int lst);
};

std::ostream& operator<<(std::ostream& os, std::vector<int> v)
{
	for (int i = 0; i < v.size(); i++) {
		os << v[i] << " ";
	}
	return os;
}

std::vector<int>& PrimeDecomp::nextPrime(std::vector<int> &primes)
{
	int p = primes.back() + 1;
	for (size_t i = 0; i < primes.size(); i++) {
		if (p % primes[i] == 0) {
			p++;
			i = 0;
		}
	}
	primes.push_back(p);
	return primes;
}

std::string PrimeDecomp::factors(int lst)
{
	typedef struct pdec_t {
		int factor;
		int times;
	} pdec_t;
	std::vector<pdec_t> v;
	std::vector<int> primes;
	primes.push_back(2);
	while (lst > 1) {
		if (lst % primes.back()) {
			primes = nextPrime(primes);
			continue;
		}
		lst /= primes.back();
		if (v.size() > 0 &&
			v.back().factor == primes.back()) {
			v.back().times++;
		} else {
			pdec_t tmp_pdec = {primes.back(), 1};
			v.push_back(tmp_pdec);
		}
	}
	std::ostringstream os;
	for (size_t i = 0; i < v.size(); i++) {
		os << "(" << v[i].factor;
		if (v[i].times > 1)
			os << "**" << v[i].times;
		os << ")";
	}
	std::cout << primes << std::endl;
	return os.str();
}

void testequal(std::string ans, std::string sol) {
	assert(ans == sol);
}

int main()
{
	using namespace std;
	vector<int> primes;
	primes.push_back(2);
	for (size_t i = 0; i < 8; i++) {
		primes = PrimeDecomp::nextPrime(primes);
		cout << primes << endl;
	}
	testequal(PrimeDecomp::factors(7775460), "(2**2)(3**3)(5)(7)(11**2)(17)");
	testequal(PrimeDecomp::factors(7919), "(7919)");
}
