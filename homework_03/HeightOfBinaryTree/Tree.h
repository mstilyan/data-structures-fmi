// https://www.hackerrank.com/challenges/tree-height-of-a-binary-tree


/*The tree node has data, left child and right child
struct node
{
int data;
node* left;
node* right;
};
*/

#include <algorithm>

struct node
{
	int data;
	node* left;
	node* right;
};

int height(node *root) 
{
	return root ? 1 + std::max(height(root->left), height(root->right)) : -1;
}
