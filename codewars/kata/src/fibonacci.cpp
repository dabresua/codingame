#include <iostream>
#include <cassert>

#include <vector>
typedef unsigned long long ull;
std::vector<ull> productFib(ull prod)
{
	ull n1 = 0, n2 = 1;
	bool found = false;
	while (n1 * n2 <= prod) {
		ull aux = 0;
		if ((prod % n2 == 0) && (prod == n1 * n2)) {
			found = true;
			break;
		}
		if (n1 * n2 > prod)
			break;
		aux = n2;
		n2 = n1 + n2;
		n1 = aux;
	}
	return {n1, n2, found};
}

int main()
{
	std::vector<ull> expected;
	expected = {55, 89, true};
	assert(productFib(4895) == expected);
	expected = {89, 144, false};
	assert(productFib(5895) == expected);
	expected = {6765, 10946, 1ULL};
	assert(productFib(74049690) == expected);
	expected = {10946, 17711, 0ULL};
	assert(productFib(84049690) == expected);

	return 0;
}
