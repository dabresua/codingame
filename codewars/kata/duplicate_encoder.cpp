#include <cassert>
#include <string>
#include <iostream>

using namespace std;

bool charcmp(char a, char b) {
	if (a == b)
		return true;
	if (a >= 'A' && a <= 'Z')
		return (a+'a'-'A') == b;
	if (a >= 'a' && a <= 'z')
		return (a+'A'-'a') == b;
	return false;
}

string duplicate_encoder(const string& word) {
	string out = word;
	bool marked[word.length()];
	for (size_t i = 0; i < word.length(); i++) {
		marked[i] = false;
	}
	for (size_t i = 0; i < word.length(); i++) {
		if (marked[i])
			continue;
		char c = word[i];
		bool rep = false;
		out[i] = '(';
		for (size_t j = i+1; j < word.length(); j++) {
			if (charcmp(c, word[j])) {
				rep = true;
				marked[j] = true;
				out[j] = ')';
				cout << "eq: " << word[j] << endl;
			}
		}
		if (rep)
			out[i] = ')';
	}
	cout << "In " << word << " Out: " << out << endl;
	return out;
}

int main()
{
	cout << "Hello" << endl;
	assert(duplicate_encoder("din").compare("(((") == 0);
	assert(duplicate_encoder("recede").compare("()()()") == 0);
	assert(duplicate_encoder("Success").compare(")())())") == 0);
	assert(duplicate_encoder("CodeWarrior").compare("()(((())())") == 0);
	assert(duplicate_encoder("Supralapsarian").compare(")()))()))))()(") == 0);
	assert(duplicate_encoder("(( @").compare("))((") == 0);
	assert(duplicate_encoder(" ( ( )").compare(")))))(") == 0);
	assert(duplicate_encoder("uR!gUMgevfaf").compare(")(())()(()()") == 0);
	return 0;
};
