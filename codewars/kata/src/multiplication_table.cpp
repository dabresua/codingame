#include <iostream>
#include <cassert>

#include <vector>

using namespace std;
vector<vector<int>> multiplication_table(int n){
	vector<vector<int>> ret(n, vector<int> (n, 0));
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < n; j++) {
			ret[i][j] = (i+1)*(j+1);
		}
	}
	return ret;
}

int main()
{
	vector<vector<int>> test({{1,2,3},{2,4,6},{3,6,9}});
	assert(multiplication_table(3) == test);

	return 0;
};
