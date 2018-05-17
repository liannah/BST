#include <iostream>
#include <set>
#include <algorithm>
#include "BST.h"
#include <numeric>

using namespace std;

int main()
{
	BinarySearchTree<int> tree;
	tree.insert(15);
	tree.insert(10);
	tree.insert(5);
	tree.insert(200);
	tree.insert(7);
	tree.insert(28);
/*
	// testing begin()
	BinarySearchTree<int>::iterator iter = tree.begin();
	cout << "minimal element is " << *iter << "\n";
	
	// testing find.
	auto iter2 = tree.find(3);
	if (iter2 == tree.end()) {
		cout << "Not found.\n";
	}
	else {
		cout << "Found " << *iter2 << "\n";
	}

	for (int val : tree) {
		cout << val << " ";
	}
	cout << endl;
	for (auto iter = tree.begin(); iter != tree.end(); ++iter) {
		cout << *iter << " "; 
	}
	cout << endl;
	cout << std::accumulate(tree.begin(), tree.end(), 0) << endl;

	for (auto iter = tree.begin(); iter != tree.end(); ++iter) {
		cout << *iter << " "; 
	}
	tree.erase(15);
	
	*/
	auto iter3 = tree.lower_bound(65);
	auto iter4 = tree.upper_bound(65);
	cout << *iter3 << endl;
	cout << *iter4 << endl;
	tree.erase(7);
	auto iter2 = tree.find(7);
	if (iter2 == tree.end()) {
		cout << "Not found.\n";
	}

	system("pause");
	return 0;
}