#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

// count points
int counter(vector<int> leftArr, vector<int> rightArr) {
	int i = 0, score = 0, result = 0;
	while (i < rightArr.size()) {
		while (score < leftArr.size() && rightArr[i] > leftArr[score]) {
			score += 1;
		}
		result += score;
		i++;
	}
	return result;
}

// Merge two sorted subvectors
void merge(vector<int>& vecRob, vector<int>& vecRach, int left, int middle, int right, int &countRob, int &countRach) {
	int leftSize = middle - left + 1;
	int rightSize = right - middle;
	vector<int> leftArrRob(leftSize); // left rob
	vector<int> rightArrRob(rightSize); // right rob
	vector<int> leftArrRach(leftSize); //left rach
	vector<int> rightArrRach(rightSize); //right rach

	//copy elements
	for (int i = 0; i < leftSize; i++) {
		leftArrRob[i] = vecRob[left + i];
		leftArrRach[i] = vecRach[left + i];
	}
	for (int i = 0; i < rightSize; i++) {
		rightArrRob[i] = vecRob[middle + i + 1];
		rightArrRach[i] = vecRach[middle + i + 1];
	}

	// count
	int iRob =0, jRob=0, iRach=0, jRach=0;
	if (iRob < leftSize && jRob < rightSize)
		countRob += counter(leftArrRach, rightArrRob);
	if (iRach < leftSize && jRach < rightSize)
		countRach += counter(leftArrRob, rightArrRach);

	// Rob merge & remaining
	int i = 0; int j = 0; int k = left;
	while (i < leftSize && j < rightSize) {
		if (leftArrRob[i] <= rightArrRob[j]) {
			vecRob[k] = leftArrRob[i];
			i++;
		}
		else {
			vecRob[k] = rightArrRob[j];
			j++;
		}
		k++;
	}
	while (i < leftSize) {
		vecRob[k] = leftArrRob[i];
		i++; k++;
	}
	while (j < rightSize) {
		vecRob[k] = rightArrRob[j];
		j++; k++;
	}

	// Rach merge & remaining
	i = 0; j = 0; k = left;
	while (i < leftSize && j < rightSize) {
		if (leftArrRach[i] <= rightArrRach[j]) {
			vecRach[k] = leftArrRach[i];
			i++;
		}
		else {
			vecRach[k] = rightArrRach[j];
			j++;
		}
		k++;
	}
	while (i < leftSize) {
		vecRach[k] = leftArrRach[i];
		i++; k++;
	}
	while (j < rightSize) {
		vecRach[k] = rightArrRach[j];
		j++; k++;
	}
}

void mergeSort(vector<int>& vecRob, vector<int>& vecRach, int left, int right, int &countRob, int &countRach) {
	if (left >= right)
		return;
	int middle = left + (right - left) / 2;

	// Sort first and second halves
	mergeSort(vecRob, vecRach, left, middle, countRob, countRach); //left half
	mergeSort(vecRob, vecRach, middle + 1, right, countRob, countRach); //right half

	// Merge the sorted halves
	merge(vecRob, vecRach, left, middle, right, countRob, countRach);
}

int main() {
	int robert, rachel;
	vector<int> rob, rach;
	string line1, line2;
	getline(cin, line1);
	getline(cin, line2);

	// process input into vectors
	istringstream st1(line1);
	istringstream st2(line2);
	while (st1 >> robert)
		rob.push_back(robert);
	while (st2 >> rachel) 
		rach.push_back(rachel);

	// merge and count
	int countRob = 0, countRach = 0;
	mergeSort(rob, rach, 0, rob.size()-1, countRob, countRach);
	cout << countRob << " " << countRach << endl;

	return 0;
}
