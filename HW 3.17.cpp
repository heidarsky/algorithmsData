#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

int findK(vector<int> arr, int l, int h) {
	if (l == h) return l;
	if (l > h) return -1;
	int mid = (l + h) / 2;

	if (mid > 0) {
		if (arr[mid] < arr[mid - 1]) {
			if (arr[mid] < arr[mid + 1])
				return mid; // minimum element
		}
	}
	if (arr[mid] > arr[h])
		return findK(arr, mid + 1, h); //right
	return findK(arr, l, mid - 1); //left
}

int biSearch(vector<int> arr, int l, int h, int k) {
	if (l > h)
		return -1; //not found

	int mid = (l + h) / 2;
	if (arr[mid] == k)
		return mid; //index

	if (arr[mid] < k)
		return biSearch(arr, mid + 1, h, k); //right
	return biSearch(arr, l, mid - 1, k); //left
}

int finder(vector<int>arr, int size, int k, int &rot) {
	rot = findK(arr, 0, size - 1); // k finder
	if (rot == -1) {
		rot = 0;
		return biSearch(arr, 0, size - 1, k); //not rotated
	}

	if (arr[rot] == k)
		return rot;
	if (arr[0] <= k)
		return biSearch(arr, 0, rot - 1, k); //left
	else
		return biSearch(arr, rot + 1, size - 1, k); //right
}


int main() {
	string line;
	int num, key;
	vector<int> arr;

	getline(cin, line);
	cin >> key;
	stringstream st(line);

	while (st >> num)
		arr.push_back(num);

	int size = arr.size();
	int rot = 0;

	//int arr[16] = {9,13,16,18,19,23,28,31,37,42,1,3,4,5,7,8};
	//int key = 33;
	//int size = sizeof(arr) / sizeof(arr[0]);

	
	//rot = findK(arr, 0, size - 1);
	//cout << rot << "\n";
	int index = finder(arr, size, key, rot);
	cout << rot << "\n" << index;

	return 0;
}
