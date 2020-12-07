#include <cassert>
#include <iostream>
#include <math.h>

long int findNextSquare(long int sq) {
	double base = sqrt(sq);
	return fmod(base,1) ? -1 : (long int)((base+1)*(base+1));
}

int main()
{
	assert(findNextSquare(121) == (144));
	assert(findNextSquare(625) == (676));
	assert(findNextSquare(319225) == (320356));
	assert(findNextSquare(15241383936) == (15241630849));
	assert(findNextSquare(155) == (-1));
	return 0;
};
