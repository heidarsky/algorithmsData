#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <string>
using namespace std;

struct node { //binary tree structure
	int val;
	node* left;
	node* right;
	node(int x) {
		val = x;
		left = nullptr;
		right = nullptr;
	}
};

//build tree
node* creatTree(vector<int>& pre, vector<int>& in, int leftPre, int leftIn, int rightIn, map<int, int>& inorder_map) {
	if (leftPre >= pre.size() || leftIn > rightIn) //empty
		return nullptr;
	
	int rootVal = pre[leftPre]; //preorder start is root
	node* root = new node(rootVal);

	int inIndex = inorder_map[rootVal]; //index of root in in-order

	//left and right trees
	root->left = creatTree(pre, in, leftPre + 1, leftIn, inIndex - 1, inorder_map);
	root->right = creatTree(pre, in, leftPre + inIndex - leftIn + 1, inIndex + 1, rightIn, inorder_map);
	return root;
}

//post-order printer
void post(node* root) { 
	if (root == nullptr)
		return;
	post(root->left);
	post(root->right);
	cout << root->val << " ";
}

int main() {
	int size = 9;
	cin >> size;
	cin.ignore(256, '\n');

	string preLine, inLine;
	getline(cin, preLine);
	getline(cin, inLine);

	vector<int> preOrder;
	vector<int> inOrder;

	stringstream preSt(preLine);
	stringstream inSt(inLine);
	int num;

	while (preSt >> num)
		preOrder.push_back(num);
	while (inSt >> num)
		inOrder.push_back(num);

	
	map<int, int> inorder_map; //values indices
	for (int i = 0; i < size; i++) {
		inorder_map[inOrder[i]] = i;
	}

	//reconstruct tree
	node* root = creatTree(preOrder, inOrder, 0, 0, size-1, inorder_map);

	//print post order
	post(root);

	return 0;
};
