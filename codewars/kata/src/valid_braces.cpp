#include <cassert>
#include <iostream>
#include <string>

bool valid_braces(std::string braces)
{
	#define CLEAN_CHAR ' '
	char exp = CLEAN_CHAR; // Expected
	char open[] =  {'(', '[', '{'};
	char close[] = {')', ']', '}'};
	int counter[] = {0,0,0};
	for (char c : braces) {
		for (unsigned short i = 0; i < 3; i++) {
			if (c == open[i]) {
				counter[i]++;
				exp = close[i];
			} else if (c == close[i]) {
				counter[i]--;
				if ((exp != close[i] && exp != CLEAN_CHAR) || counter[i] < 0) {
					return false;
				}
				exp = CLEAN_CHAR;
			}
		}
	}
	return !counter[0] && !counter[1] && !counter[2];
}

int main(void)
{
	assert( valid_braces("()") == true );
	assert( valid_braces("[(])") == false );
	assert( valid_braces("([{}])") == true );
};
