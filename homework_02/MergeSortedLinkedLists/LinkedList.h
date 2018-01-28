/*
Merge two sorted lists A and B as one linked list
Node is defined as
struct Node
{
int data;
struct Node *next;
}
*/

#ifndef LINKED_LIST
#define LINKED_LIST

struct node
{
	int data;
	struct node *next;
};

node* MergeLists(node *headA, node* headB)
{
	if (headA == nullptr) return headB;
	if (headB == nullptr) return headA;

	if (headA->data < headB->data)
	{
		headA->next = MergeLists(headA->next, headB);
		return headA;
	}
	if (headB->data <= headA->data)
	{
		headB->next = MergeLists(headA, headB->next);
		return headB;
	}

	return nullptr;
}

#endif 