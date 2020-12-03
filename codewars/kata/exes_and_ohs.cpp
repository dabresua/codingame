#include <cassert>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

bool XO(const std::string& str)
{
	std::string low;
	for(char c : str)
		low+=std::tolower(c);
	return std::count_if(low.begin(), low.end(),[](char c){return c==('x');}) ==
	       std::count_if(low.begin(), low.end(),[](char c){return c==('o');});
}

int main()
{
	assert(XO("ooxx") == true);
	assert(XO("xooxx") == false);
	assert(XO("ooxXm") == true);
	assert(XO("zpzpzpp") == true);
	assert(XO("zzoo") == false);
	return 0;
};
