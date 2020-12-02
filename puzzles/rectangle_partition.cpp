#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

/* #define DEBUG */

#define ALGORITHM 2

static int counter = 0;

#ifdef DEBUG
void debug_squares(int *x, int *y, int lenx, int leny)
{
	cerr << endl;
	string space = "  ";
	string dash = "__";
	string line_empty = "|";
	string line_set = "|";
	string line_upper = "0";
	string blank = " ";
	int ix = 0;
	for (int i = 1; i <= x[lenx-1]; i++) {
		line_empty += space;
		line_set += dash;
		line_upper += dash;
		if (i == x[ix]) {
			line_empty += "|";
			line_set += "|";
			line_upper += to_string(i%10);
			ix++;
		}
	}

	cerr << " " << line_upper << endl;
	int iy = 0;
	for (int i = 1; i <= y[leny-1]; i++) {
		if (i == y[iy]) {
			cerr << (y[iy]%10) << line_set << endl;
			iy++;
		} else {
			cerr << " " << line_empty << endl;
		}
	}
	cerr << endl;
}
#endif /* DEBUG */

static
int find_o_square(int c, int r, int *subc, int *subr, int lenc, int lenr)
{
	#ifdef DEBUG
	cerr << "[" << subr[0] << "," << subc[0] << "]"
	     << "[" << subr[lenr-1] << "," << subc[lenc-1] << "]" << endl;
	#endif /* DEBUG */
	int ret = 0;
	for (size_t i = 0; i < lenc; i++) {
		for (size_t j = 0; j < lenr; j++) {
			counter++;
			if ((subc[i] - c)  == (subr[j] - r)) {
				#ifdef DEBUG
				cerr << "square at " << subr[j] << "," << subc[i] << " ret "
				     << ret+1 << endl;
				#endif /* DEBUG */
				ret++;
				break;
			}
		}
	}
	return ret;
}

static
int find_o_log(int c, int r, int *subc, int *subr, int lenc, int lenr)
{
	#ifdef DEBUG
	cerr << "[" << subr[0] << "," << subc[0] << "]"
	     << "[" << subr[lenr-1] << "," << subc[lenc-1] << "]" << endl;
	#endif /* DEBUG */
	int ret = 0;
	for (size_t i = 0; i < lenc; i++) {
		//cerr << i << " " << subc[i] << endl;
		int j = lenr/2;
		int min = 0;
		int max = lenr;
		while (j >= min && j <= max) {
			counter++;
			int diff = (subc[i] - c) - (subr[j] - r);
			//cerr << "testing " << subr[j] << "," << subc[i] << " ret "
			//     << ret+1 << " diff " << diff << endl;
			if (diff == 0) {
				#ifdef DEBUG
				cerr << "square at " << subr[j] << "," << subc[i] << " ret "
				     << ret+1 << endl;
				#endif /* DEBUG */
				ret++;
				break;
			}
			if (min == max)
				break;
			if (diff > 0) {
				//cerr << " j init " << j;
				min = j + 1;
				j = (max-j)/2 + j + ((max-j)%2>0?1:0);
				//cerr << " j " << j << " min " << min << " max " << max << endl;
			} else {
				max = j - 1;
				j = (j-min)/2 + min;
			}
			//cerr << "min " << min << " j " << j << " max " << max << endl;
		}
	}
	return ret;
}

static
int calculate_squares(int *x, int *y, int lenx, int leny)
{
	int squares = 0;
	int cols [lenx];
	cols[0] = 0;
	memcpy(&cols[1], x, (lenx-1)*sizeof(int));
	int rows [leny];
	rows[0] = 0;
	memcpy(&rows[1], y, (leny-1)*sizeof(int));

	int subc[lenx], subr[leny];

	for (int i = 0; i < lenx*leny; i++) {
		int r = i/lenx;
		int c = i%lenx;
		#ifdef DEBUG
		cerr << "[" << rows[r] << "," << cols[c] << "] ---------------" << endl;
		#endif /* DEBUG */
		memcpy(subc, &cols[c+1], (lenx-c-1)*sizeof(int));
		subc[lenx-c-1] = x[lenx-1];
		memcpy(subr, &rows[r+1], (leny-r-1)*sizeof(int));
		subr[leny-r-1] = y[leny-1];
		#ifndef ALGORITHM
		#error ALGORITHM must be defined
		#endif /* ALGORITHM */
		switch (ALGORITHM) {
		case 1:
			squares += find_o_square(cols[c], rows[r], subc, subr, lenx-c, leny-r);
			break;
		case 2:
			squares += find_o_log(cols[c], rows[r], subc, subr, lenx-c, leny-r);
			break;
		default:
			assert(false);
		}
	}

	return squares;
}

int main()
{
	int w;
	int h;
	int countX;
	int countY;
	cin >> w >> h >> countX >> countY; cin.ignore();
	#ifdef DEBUG
	cerr << "w " << w << " h " << h << " xn " << countX << " yn " << countY
	     << endl;
	#endif /* DEBUG */
	int x[countX+1];
	x[countX] = w;
	for (int i = 0; i < countX; i++) {
		cin >> x[i]; cin.ignore();
		#ifdef DEBUG
		cerr << "x " << x[i] << endl;
		#endif /* DEBUG */
	}
	int y[countY+1];
	y[countY] = h;
	for (int i = 0; i < countY; i++) {
		cin >> y[i]; cin.ignore();
		#ifdef DEBUG
		cerr << "y " << y[i] << endl;
		#endif /* DEBUG */
	}

	#ifdef DEBUG
	debug_squares(x, y, countX+1, countY+1);
	#endif /* DEBUG */
	cout << calculate_squares(x, y, countX+1, countY+1) << endl;

	#ifdef DEBUG
	cerr << "counter " << counter << endl;
	#endif /* DEBUG */
}
