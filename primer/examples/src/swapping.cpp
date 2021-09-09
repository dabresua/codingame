#include <iostream>
#include <string>
#include <vector>

void swap_a(int* pa, int* pb)
{
	int tmp = *pa;
	*pa = *pb;
	*pb = tmp;
}

void swap_b(int a, int b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

void swap_c(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

void copy(int &a, const int &b)
{
	a = b;
}

void print(const int &a, const int &b)
{
	std::cout << a << ":" << b << std::endl;
}

const std::string & version(std::string & s1, const std::string & s2)
{
	s1 = s2 + ", " + s1 + " " + s2;
	return s1;
}

const std::string & version2(const std::string & s1, const std::string & s2)
{
	std::string temp;
	temp = s2 + ", " + s1 + " " + s2;
	return temp; // Too bad, out of scope -> crash. At least, the compiler shows a warning
}

int sum(int a, int b = 7)
{
	return a + b;
}

long sum(long a, long b = 2)
{
	return a + b;
}

bool division(bool a, bool b)
{
	return false;
}

template <class T>
T division(T a, T b)
{
	return a/b;
}

template <> char division<char>(char a, char b)
{
	return 'c';
}

std::ostream& operator<<(std::ostream& os, std::vector<int> v)
{
	for (int i = 0; i < v.size(); i++) {
		os << v[i] << " ";
	}
	return os;
}

int main() {
	using namespace std;
	#define PRINT cout << "a=" << a << " b=" << b << endl;

	cout << "--- Pointers ---" << endl;
	int a = 1, b = 2;
	PRINT
	swap_a(&a, &b);
	PRINT

	cout << "--- Value ---" << endl;
	a = 1, b = 2;
	PRINT
	swap_b(a, b);
	PRINT

	cout << "--- Reference ---" << endl;
	a = 1, b = 2;
	PRINT
	swap_c(a, b);
	PRINT

	cout << " --- STL --- " << endl;
	a = 1, b = 2;
	PRINT
	std::swap(a, b);
	PRINT
	std::vector<int> av(7,5), bv(15,16);
	cout << "av " << av << endl;
	cout << "bv " << bv << endl;
	std::swap(av, bv);
	cout << "av " << av << endl;
	cout << "bv " << bv << endl;

	# if 0
	cout << "--- Reference bad ---" << endl;
	a = 1, b = 2;
	PRINT
	swap_c(a, (b+2)); // Does not compile -> b+2 is a temporal variable, does not have a valid address
	PRINT
	#endif /* 0 */

	cout << "--- Copy ---" << endl;
	a = 1, b = 2;
	PRINT
	copy(a, (b+2));
	PRINT

	char c = 1, d = 2;
	//swap_a(&c, &d); //NOK
	swap_a((int *)&c,(int *)&d); //Ok, casting
	swap_b(c, d); // Ok, auto-casting
	//swap_c(c, d); //NOK, cannot bind non-constant lvalue
	//swap_c((int)c,(int)d); //NOK, same error
	print(a,b); //Ok because const references

	string s1 = "James";
	string s2 = "Bond";
	string r;
	cout << s1 << " " << s2 << endl;
	r = version(s1, s2);
	cout << s1 << " " << s2 << endl;
	cout << r << endl;
	cout << &s1 << " " << &s2 << " " << &r << endl;

	#if 0
	s1 = "James";
	s2 = "Bond";
	r = version2(s1, s2); // Generates core
	cout << s1 << " " << s2 << endl;
	cout << r << endl;
	#endif /* 0 */

	cout << sum(1,1) << " " << sum(1) << endl;
	cout << sum((long)1,(long)1) << " " << sum((long)1) << endl;

	int ia = 7, ib = 2;
	double da = 7, db = 2;
	bool ba = true, bb = true;
	char ca = 'a', cb = 'B';
	cout << division(ia, ib) << " " << division(da, db) << endl;
	cout << true/true << " " << division(ba, bb) << " " << 'a'/'B' << " " << division(ca, cb) << endl;

	return 0;
}
