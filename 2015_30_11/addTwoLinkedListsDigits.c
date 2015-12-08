#include <stdio.h>
#include <malloc.h>
#define MAX 15

struct testCases {
	int a[MAX], n1, b[MAX], n2, r[MAX], n;
}cases[] = {
	{
		{ 1, 2, 3, 4, 5 }, 5,{ 1, 2, 3, 4, 4 }, 5,{ 2, 4, 6, 8, 9 }, 5
	},
	{
		{ 1, 2, 3, 4, 5 }, 5,{ 1, 2, 3, 4, 5 }, 5,{ 2, 4, 6, 9, 0 }, 5
	},
	{
		{ 1, 2, 3, 4, 5 }, 5,{ 9, 0, 0, 0, 0 }, 5,{ 1, 0, 2, 3, 4, 5 }, 6
	},
	{
		{ 1, 2 }, 2,{ 1, 2, 3 }, 3,{ 1, 3, 5 }, 3
	},
	{
		{ 1, 2, 3 }, 3,{ 1, 2 }, 2,{ 1, 3, 5 }, 3
	},
	{
		{ -1 }, 0,{ 1 }, 1,{ 1 }, 1
	},
	{
		{ 1 }, 1,{ -1 }, 0,{ 1 }, 1
	},
	{
		{ -1 }, 0,{ -1 }, 0,{ -1 }, 0
	}
};

struct node {
	int n;
	struct node *next;
};

// reverse a linked list
void reverse(struct node** head)
{
	//handling exceptions
	if (!(*head) || !((*head)->next))
		return;

	// dividing list to first element and rest of list
	struct node *first = *head, *rest = (*head)->next;
	reverse(&rest);
	// reversing links
	first->next->next = first;
	first->next = NULL;
	*head = rest;
}

struct node * add(struct node *num1, struct node* num2) {
	reverse(&num1);
	reverse(&num2);
	struct node *temp1 = num1;
	struct node *temp2 = num2;
	int carry = 0;
	while (temp1 && temp2) {
		temp1->n += temp2->n + carry;
		carry = 0;
		if (temp1->n > 9) {
			temp1->n -= 10;
			carry++;
		}
		temp1 = temp1->next;
		temp2 = temp2->next;
	}
	if (!temp1 && !temp2) {
		if (carry) {
			struct node *newNode = malloc(sizeof(struct node));
			newNode->n = 1;
			reverse(&num1);
			newNode->next = num1;
			return newNode;
		}
		else {
			reverse(&num1);
			return num1;
		}
	}
	else if (!temp1) {
		temp2->n += carry;
		reverse(&temp2);
		struct node *temp3 = temp2;
		while (temp3->next) temp3 = temp3->next;
		reverse(&num1);
		temp3->next = num1;
		return temp2;
	}
	else {
		temp1->n += carry;
		reverse(&num1);
		return num1;
	}
}

// creates linked list of elements from array
struct node * createList(int *list, int n) {
	struct node * head = NULL;
	while (n--) {
		struct node *temp = (struct node *)malloc(sizeof(struct node));
		temp->next = head;
		temp->n = list[n];
		head = temp;
	}
	return head;
}

int compareLists(struct node * a, struct node * b) {
	while (a && b && a->n == b->n) {
		a = a->next;
		b = b->next;
	}
	return !(a || b);
}

void tester(int n) {
	int i;
	for (i = 0; i < n; i++)
		if (compareLists(add(createList(cases[i].a, cases[i].n1), createList(cases[i].b, cases[i].n2)), createList(cases[i].r, cases[i].n)))
			printf("PASS\n");
		else
			printf("FAIL\n");
}

int main(void) {
	tester(8);
	getchar();
}