/*
Reverse a doubly linked list, input list may also be empty
Node is defined as
struct Node
{
int data;
Node *next;
Node *prev;
}
*/
#ifndef LINKED_LIST
#define LINKED_LIST

struct node
{
	int data;
	node *next;
	node *prev;
};

node* Reverse(node* head)
{
	if (head == nullptr) return head;

	while (true)
	{
		node* next = head->next;

		node* temp = head->next;
		head->next = head->prev;
		head->prev = temp;

		if (next != nullptr) head = next;
		else break;
	}

	return head;
}

#endif
