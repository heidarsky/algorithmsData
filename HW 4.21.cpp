#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// checks current symbol-digit mapping
bool valid(vector<int>& digits, string& str1, string& str2, string& str3, int index, int temp) {
	if (index == str3.size())
		return temp == 0;

	int digit1, digit2, digit3;
	digit1 = 0, digit2 = 0; digit3 = 0;

	//digits for symbols
	if (index < str1.size())
		digit1 = digits[str1[index] - 'A'];
	if (index < str2.size())
		digit2 = digits[str2[index] - 'A'];
	digit3 = digits[str3[index] - 'A'];

	int sum = digit1 + digit2 + temp; // check sum with third string
	if (sum % 10 != digit3)
		return false;
	return valid(digits, str1, str2, str3, index + 1, sum / 10); //next 
}

//backtracking
bool backT(vector<int>& digits, vector<bool>& usedDig, string& symbols, string& str1, string& str2, string& str3, int index) {
	if (index == symbols.size())
		return valid(digits, str1, str2, str3, 0, 0);

	//possible combinations
	for (int dig = 0; dig <= 9; dig++) {
		if (!usedDig[dig]) {
			digits[symbols[index] - 'A'] = dig; //digit to current
			usedDig[dig] = true;
			if (backT(digits, usedDig, symbols, str1, str2, str3, index + 1)) //next symbol
				return true;

			usedDig[dig] = false; //unused
		}
	}
	return false;
}

int main() {
	string symbols, str1, str2, str3;
	cin >> symbols; cin >> str1; cin >> str2; cin >> str3;
	reverse(symbols.begin(), symbols.end()); //for easier addition
	reverse(str1.begin(), str1.end());
	reverse(str2.begin(), str2.end());
	reverse(str3.begin(), str3.end());

	//cout << symbols << "\n" << str1 << " " << str2 << " " << str3;

	//initialize mapping
	vector<int> digits(26, -1);
	vector<bool> usedDig(10, false);

	if (!backT(digits, usedDig, symbols, str1, str2, str3, 0)) {
		cout << "No solution.";
	}
	else {
		reverse(symbols.begin(), symbols.end()); //reverse back for printing
		for (char sym : symbols)
			cout << digits[sym - 'A'];
		cout << endl;
	}
	return 0;
};
