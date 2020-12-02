#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

typedef enum move_t {
	move_u,
	move_d,
	move_r,
	move_l,
} move_t;

string move2str(move_t m) {
	switch (m) {
	case move_u: return "UP";
	case move_d: return " DOWN";
	case move_r: return "RIGHT";
	case move_l: return "LEFT";
	default: assert(false);
	}
	return "";
}

int main()
{
	int R; // number of rows.
	int C; // number of columns.
	int A; // number of rounds between the time the alarm countdown is activated and the time the alarm goes off.
	cin >> R >> C >> A; cin.ignore();

	// game loop
	while (1) {
		int KR; // row where Kirk is located.
		int KC; // column where Kirk is located.
		cin >> KR >> KC; cin.ignore();
		cerr << "KR " << KR << " KC " << KC << endl;
		for (int i = 0; i < R; i++) {
			string ROW; // C of the characters in '#.TC?' (i.e. one line of the ASCII maze).
			cin >> ROW; cin.ignore();
			
			cerr << "ROW " << ROW << endl;
		}

		cout << "RIGHT" << endl; // Kirk's next move (UP DOWN LEFT or RIGHT).
	}
}
