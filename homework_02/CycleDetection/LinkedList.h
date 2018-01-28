/*
Detect a cycle in a linked list. Note that the head pointer may be 'NULL' if the list is empty.

A Node is defined as:
struct Node {
int data;
struct Node* next;
}
*/

#ifndef LINKED_LIST
#define LINKED_LIST

struct node
{
	int data;
	struct node *next;
};

bool has_cycle(node *head)
{
	node* fast = head;
	node* slow = head;

	while (fast && slow && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
		if (fast == slow) return true;
	}

	return false;
}

#endif 