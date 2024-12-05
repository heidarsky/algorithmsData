#include <iostream>
using namespace std;

int lastRecur(int listofN) {
	if (listofN == 1) // size 1
		return 1;
	int halfList = listofN / 2;
	// divide list recursively until 1 , mult by 2
	int rec = 2*halfList - 2*lastRecur(halfList) + 2; //recursion - recurrence relation / dynamic prog
	return rec; //recursion
}

int main() {
	// list of numbers from [1, listOfN]
	int listOfN;
	cin >> listOfN;

	int res = lastRecur(listOfN);
	cout << res << endl;

	return 0;
}
