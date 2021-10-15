#include <string>
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>

class Decomp
{
public:
	/**
	 * @brief Decomposes a number into fractions
	 *        n = num/den; n >= 0
	 *        n = n_a + n_b/den
	 *        n_b/den = 1/d_1 + 1/d_2 + ... + 1/d_N; N < inf
	 *        Find next factor that:
	 *             n_b/den - 1/fact >= 0 -> n_b * fact - den >= 0
	 *        Again the next factor should be:
	               n_b/den >= 1/fact -> fact >= den/n_b
	 *        So there is no need to try 2,3,4,... we can skip those
	 */
	static std::string decompose(const std::string &nrStr,
	                             const std::string &drStr)
	{
		long num = std::stol(nrStr);
		long den = std::stol(drStr);
		long n_a = num/den;
		long n_b = num%den;
		std::ostringstream result;
		result << "[";
		bool first_ch = true;
		if (n_a) {
			result << n_a;
			first_ch = false;
		}
		long fact;
		if (n_b)
			fact = den/n_b;
		while (n_b > 0) {
			if (n_b * fact - den >= 0) {
				n_b = n_b * fact - den;
				den *= fact;
				// Must simplify fractions for very big numbers
				if (!first_ch)
					result << ", ";
				result << "1/" << fact;
				first_ch = false;
				// skip to next factor
				if (n_b)
					fact = den/n_b;
			} else {
				// Integers are used, so den/n_b could not be the next factor
				fact++;
			}
		}
		result << "]";
		return result.str();
	}
};


void testequal(std::string ans, std::string sol) {
	std::cout << ans << std::endl;
	std::cout << sol << std::endl;
	assert(ans == sol);
}

int main()
{
	std::cout << Decomp::decompose("22", "7") << std::endl;

	testequal(Decomp::decompose("3", "4"), "[1/2, 1/4]");
	testequal(Decomp::decompose("12", "4"), "[3]");
	testequal(Decomp::decompose("4", "5"), "[1/2, 1/4, 1/20]");
	testequal(Decomp::decompose("66", "100"), "[1/2, 1/7, 1/59, 1/5163, 1/53307975]");

	testequal(Decomp::decompose("1001", "3456"), "[1/4, 1/26, 1/848, 1/2381184]");
	testequal(Decomp::decompose("30", "45"), "[1/2, 1/6]");
	testequal(Decomp::decompose("50", "4187"), "[1/84, 1/27055, 1/1359351420]");

}
