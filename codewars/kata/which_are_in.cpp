#include <cassert>
#include <iostream>
#include <string>
#include <vector>

static std::vector<std::string> inArray(std::vector<std::string> &array1,
                                        std::vector<std::string> &array2)
{
	std::vector<std::string> res;
	for (std::string str1 : array1) {
		for (std::string str2 : array2) {
			if (str2.find(str1) != std::string::npos) {
				res.push_back(str1);
				break;
			}
		}
	}
	sort(res.begin(), res.end());
	return res;
}

int main()
{
	std::vector<std::string> arr1 = { "arp", "live", "strong" };
	std::vector<std::string> arr2 = { "lively", "alive", "harp", "sharp", "armstrong" };
	std::vector<std::string> sol1 = { "arp", "live", "strong" };

	assert(inArray(arr1, arr2) == sol1);
	return 0;
};
