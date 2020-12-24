#include<vector>
#include <cassert>

bool isValidWalk(std::vector<char> walk) {
	if (walk.size() != 10)
		return false;
	int ns = 0, ew = 0;
	for (char c : walk) {
		switch (c) {
		case 'n': ns++; break;
		case 's': ns--; break;
		case 'e': ew++; break;
		case 'w': ew--; break;
		default: assert(false);
		}
	}
	return !ns && !ew;
}

int main(void)
{
	using V = std::vector<char>;
	assert(isValidWalk(V{'n'}) == (false));
	assert(isValidWalk(V{'n','s','n','s','n','s','n','s','n','s'}) == (true));
	assert(isValidWalk(V{'n','s'}) == (false));
	assert(isValidWalk(V{'n','s','n','s','n','s','n','s','n','s','n','s'}) == (false));
	assert(isValidWalk(V{'e','w','e','w','n','s','n','s','e','w'}) == (true));
	assert(isValidWalk(V{'n','s','e','w','n','s','e','w','n','s','e','w','n','s','e','w'}) == (false));
	assert(isValidWalk(V{'n','s','e','w','n','s','e','w','n','s'}) == (true));
	assert(isValidWalk(V{'s','e','w','n','n','s','e','w','n','s'}) == (true));
	assert(isValidWalk(V{'n','s','n','s','n','s','n','s','n','n'}) == (false));
	assert(isValidWalk(V{'e','e','e','w','n','s','n','s','e','w'}) == (false));
	return 0;
}
