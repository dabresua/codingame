#include <iostream>
#include <cstdint>
#include <climits>
#include <exception>

using namespace std;

class BootstrapTest {
private:
	static int counter;
public:
	BootstrapTest() {
		counter++;
		cout << "Bootstrap is f***ing awesome " << counter << endl;
	}
	~BootstrapTest() {
		--counter;
		cout << "Hasta la vista baby " << counter << endl;
	}
	friend ostream& operator <<(ostream &os, const BootstrapTest &b);
};

ostream& operator <<(ostream &os, const BootstrapTest &b)
{
	os << "counter [" << b.counter << "]";
	return os;
}

int BootstrapTest::counter = 0; /* Allocation and initialization for shared counter */
BootstrapTest b1;
BootstrapTest b2;

void createTest(void) {
	cout << "test!!!" << endl;
	BootstrapTest a;
	cout << "b1 " << b1 << " b2 " << b2 << endl;
	cout << "a " << a << endl;
	cout << "----" << endl;
}

int main()
{
	cout << "Hello" << endl;
	cout << "b1 " << b1 << " b2 " << b2 << endl;
	createTest();
	cout << "b1 " << b1 << " b2 " << b2 << endl;

	cout << "int    " << sizeof(int)    << " bytes" << endl;
	cout << "long   " << sizeof(long)   << " bytes" << endl;
	cout << "short  " << sizeof(short)  << " bytes" << endl;
	cout << "char   " << sizeof(char)   << " bytes" << endl;
	cout << "bool   " << sizeof(bool)   << " bytes" << endl;
	cout << "float  " << sizeof(float)  << " bytes" << endl;
	cout << "double " << sizeof(double) << " bytes" << endl;
	cout << "L doub " << sizeof(long double) << " bytes" << endl;

	cout << "uint8  " << sizeof(uint8_t)  << " bytes" << endl;
	cout << "uint16 " << sizeof(uint16_t) << " bytes" << endl;
	cout << "uint32 " << sizeof(uint32_t) << " bytes" << endl;
	cout << "uint64 " << sizeof(uint64_t) << " bytes" << endl;

	cout << "fast uint8  " << sizeof(uint_fast8_t)  << " bytes" << endl;
	cout << "fast uint16 " << sizeof(uint_fast16_t) << " bytes" << endl;
	cout << "fast uint32 " << sizeof(uint_fast32_t) << " bytes" << endl;
	cout << "fast uint64 " << sizeof(uint_fast64_t) << " bytes" << endl;

	cout << "least uint8  " << sizeof(uint_least8_t)  << " bytes" << endl;
	cout << "least uint16 " << sizeof(uint_least16_t) << " bytes" << endl;
	cout << "least uint32 " << sizeof(uint_least32_t) << " bytes" << endl;
	cout << "least uint64 " << sizeof(uint_least64_t) << " bytes" << endl;

	cout << "uintmax_t " << sizeof(uintmax_t) << " bytes" << endl;
	cout << "uintptr_t " << sizeof(uintptr_t) << " bytes" << endl;

	unsigned long a = LONG_MAX;
	unsigned int b = a;
	unsigned int c = (unsigned int)a;
	unsigned int d = static_cast<unsigned int> (a);

	cout << a << ", " << b << ", " << c << ", " << d << endl;

	long x1 = 1, x2 = 2;
	int sum = static_cast<int> (x1) + static_cast<int> (x2);

	short things[] = {1, 5, 3, 8};
	int num_elements = sizeof things / sizeof (short);
	cout << things << " -> " << num_elements << endl;

	char dog[5] = {'a','b','c','d','e'};
	char cat[5] = {'A','B','C','D','\0'};
	cout << "cat " << cat << endl;
	cout << "dog " << dog << endl;

	enum pepe{pepe_a = 0, pepe_b = 128};
	enum paco{paco_a = 0, paco_b = 1};
	enum pipo{pipo_a = 0, pipo_b = 10000000000L};

	struct payo {
		bool p:1;
	};

	struct piyo {
		bool p;
	};

	cout << sizeof(pepe) << " " << sizeof(paco) << " " << sizeof(pipo) << endl;
	cout << sizeof(payo) << " " << sizeof(piyo) << " " << sizeof(bool) << endl;

	int i;
	int* pi = &i;
	cout << sizeof(i) << " " << sizeof(pi) << " " << sizeof(*pi) << endl;

	/* this will throw a core */
	#if 0
	int* pnull = 0;
	try {
		*pnull = 0;
	} catch (exception& e) {
		cout << "hard-core: " << e.what() << endl;
	}
	#endif /* 0 */

	int size;
	cout << "Write size: ";
	cin >> size;
	int *array = new int[size];
	cout << sizeof(array) << endl;
	delete [] array;
	BootstrapTest *tests = new BootstrapTest[size];
	delete [] tests;

	cout << (int *) "Home of the jolly bytes" << endl;

	#if 0
	int arr[7] = {1,2,3,4,5,6,7};
	arr[8] = 8;
	for (unsigned int i = 0; i <= 8; i++) {
		cout << arr[i] << endl; // segment fault
	}
	#endif /* 0 */

	int rats = 3;
	int & rodents = rats;
	cout << rats << " " << rodents << endl;
	cout << &rats << " " << &rodents << endl;
	int dogs = 4;

	return 0;
}
