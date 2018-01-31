//https://www.hackerrank.com/challenges/tree-huffman-decoding/problem

/*
The structure of the node is

typedef struct node
{
int freq;
char data;
node * left;
node * right;

}node;

*/
#ifndef TREE
#define TREE

#include <string>
#include <iostream>

typedef struct node
{
	int freq;
	char data;
	node * left;
	node * right;
}node;

void decode_huff(node * root, std::string s)
{
	node* curr = root;
	for (auto ch : s)
	{
		switch (ch)
		{
		case '1':
			curr = curr->right;
			break;
		case '0':
			curr = curr->left;
			break;
		}

		if (curr->data != '\0')
		{
			std::cout << curr->data;
			curr = root;
		}
	}
}

#endif
