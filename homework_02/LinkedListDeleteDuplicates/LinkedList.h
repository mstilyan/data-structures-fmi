/*
Remove all duplicate elements from a sorted linked list
node is defined as
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

node* removeDuplicates(node *head)
{
	node* result = head;

	while (head != nullptr)
	{
		node* prev = head;
		node* curr = head->next;

		while (curr != nullptr)
		{
			if (curr->data == head->data)
			{
				prev->next = curr->next;
				delete curr;
				curr = prev->next;
			}
			else
			{
				curr = curr->next;
				prev = prev->next;
			}
		}

		head = head->next;
	}

	return result;
}


#endif 
