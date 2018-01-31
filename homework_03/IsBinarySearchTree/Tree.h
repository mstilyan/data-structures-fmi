/* Hidden stub code will pass a root argument to the function below. Complete the function to solve the challenge.
 * Hint: you may want to write one or more helper functions.
 * 
 * The Node struct is defined as follows:
 * struct Node {
 * int data;
 * Node* left;
 * Node* right;
}*/

#ifndef TREE
#define TREE

#include <cstdint>

struct Node
{
	int data;
	Node* left;
	Node* right;
};

bool checkBST(Node* root, int min = INT32_MIN, int max = INT32_MAX)
{
	if (!root) return true;

	return (root->data > min && root->data < max) &&
		checkBST(root->left, min, root->data) &&
		checkBST(root->right, root->data, max);
}

#endif
