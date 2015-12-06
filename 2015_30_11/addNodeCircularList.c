#include <stdio.h>
#include <malloc.h>
#define MAX 15

struct testCases {
	int a[MAX], n, value, index, r[MAX], rSize;
}cases[] = {
	{
		{ 1, 2, 3, 4, 5 }, 5, 6, 5,{ 1, 2, 3, 4, 5, 6 }, 6
	},
	{
		{ 1, 2, 3, 4, 5 }, 5, -1, 0,{ -1, 1, 2, 3, 4, 5 }, 6
	},
	{
		{ 1, 2, 4, 5 }, 4, 3, 2,{ 1, 2, 3, 4, 5 }, 5
	},
	{
		{ -1 }, 0, 25, 0,{ 25 }, 1
	},
	{
		{ -1 }, 1, 25, 0,{ 25, -1 }, 2
	},
	{
		{ -1 }, 1, 25, 1,{ -1, 25 }, 2
	}
};

struct node {
	int data;
	struct node *next;
};

struct node * insertAtIndex(struct node * head, int data, int index) {
	struct node* newNode = malloc(sizeof(struct node));
	newNode->data = data;
	// returning circular list with single element in case of empty list
	if (!head) {
		newNode->next = newNode;
		return newNode;
	}
	struct node *temp = head;
	// inserting at beginning
	if (!index) {
		newNode->next = head;
		while (temp->next != head)
			temp = temp -> next;
		temp->next = newNode;
		return newNode;
	}
	// inserting and any index
	while (--index)
		temp = temp->next;
	struct node *temp1 = temp->next;
	temp->next = newNode;
	newNode->next = temp1;
	return head;
}

// creates linked list of elements from array
struct node * createList(int *list, int n) {
	int i = n;
	struct node * head = NULL, *tail = NULL;
	while (n--) {
		struct node *temp = (struct node *)malloc(sizeof(struct node));
		temp->next = head;
		temp->data = list[n];
		head = temp;
		if (n == i - 1) {
			tail = temp;
		}
	}
	if(tail)
		tail->next = head;
	return head;
}

int compareLists(struct node * a, struct node * b, int n) {
	if (!n)
		return a == NULL;
	while (n-- && a && b && a->data == b->data) {
		a = a->next;
		b = b->next;
	}
	return a->data == b->data;
}

void tester(int n) {
	int i;
	for (i = 0; i < n; i++)
		if (compareLists(insertAtIndex(createList(cases[i].a, cases[i].n), cases[i].value, cases[i].index), createList(cases[i].r, cases[i].rSize), cases[i].rSize))
			printf("PASS\n");
		else
			printf("FAIL\n");
}

int main(void) {
	tester(6);
	getchar();
}