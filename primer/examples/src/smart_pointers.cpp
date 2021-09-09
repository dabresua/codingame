#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class Test
{
private:
	int* n;
	static const int SIZE = 7;
public:
	Test()
	{
		cout << "calling constructor" << endl;
		n = new int[SIZE]{1,2,3,4,5,6,7};
	}

	~Test()
	{
		cout << "calling destructor" << endl;
		delete []n;
	}

	friend ostream& operator <<(ostream &os, const Test &t);
};

ostream& operator <<(ostream &os, const Test &t)
{
	for (size_t i = 0; i < t.SIZE; i++) {
		os << t.n[i] << " ";
	}
	return os;
}

int main()
{
	string line = string(80,'-');
	cout << line << endl;
	{
		Test t;
		cout << t << endl;
		// Will call destructor
	}

	cout << line << endl;
	{
		Test *tests = new Test();
		// Won't call destructor at the end of the scope
		// Memory leak!!!
	}

	cout << line << endl;
	{
		unique_ptr<Test> smart(new Test());
		// This way will call destructor
	}

	cout << line << endl;
	{
		// with arrays
		unique_ptr<Test[]> smart(new Test[5]);
		// This way will call destructor
	}

	cout << line << endl;
	{
		// with vectors
		vector<Test> vec(5);
	}
	return 0;
}
