/*
struct node
{
int data;
node* left;
node* right;
}*/

#ifndef TREE
#define TREE

#include <iostream>
#include <queue>

struct node
{
	int data;
	node* left;
	node* right;
};


void levelOrder(node* root)
{
	if (!root) return;

	std::cout << root->data;
	std::queue<node*> q;
	q.push(root);

	while (!q.empty())
	{
		node* node = q.front();
		std::cout << node->data << " ";

		if (node->left) q.push(node->left);
		if (node->right) q.push(node->right);

		q.pop();
	}
}

#endif
