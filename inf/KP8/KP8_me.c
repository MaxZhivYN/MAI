#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct node{
	int data;
	struct node *next;
};

void PrintList(struct node ** head)
{
	struct node *temp;
	temp = *head;
	if(temp == NULL)
	{
		printf("List is empty");
		return;
	}

	while(temp->next != NULL)
	{
		printf("%d ",temp->data);
		temp = temp->next;
	}
	printf("\n");
	return;
}

void AddNode(struct node **head, int position, int value)
{
	int currentNodePosition = 1;
	struct node *temp, *newNode;
	newNode = (struct node *)malloc(sizeof(struct node));

	if (*head == NULL)
	{
		printf("\nList Empty.");
		position = 1;

	}
	if (!newNode)
	{
		printf("\nError while allocating memory to new Node");
		return;
	}
	newNode->data = value;
	if(position == 1)
	{
		newNode->next = *head;
		*head = newNode;
		return;
	}
	temp = *head;
	while((currentNodePosition < position - 1) && (temp->next != NULL))
	{
		temp = temp->next;
		currentNodePosition++;
	}
	
	newNode->next = temp->next;
	temp->next = newNode;
	return;
}

void DeleteNodeFromList(struct node **head, int position)
{
	struct node *temp, *temp2;
	temp = *head;
	int currentNodePosition = 1;

	if(*head == NULL)
	{
		printf("\nList is empty");
		return;
	}

	if(position == 1)
	{
		*head = temp->next;
		free(temp);
		return;
	}

	while((currentNodePosition < position - 1) && (temp != NULL))
	{
		temp = temp->next;
		currentNodePosition++;
	}
	if (temp->next != NULL) {
		temp2 = temp->next;
		temp->next = temp2->next;
		free(temp2);
	}
	return;
}

int CountNodesInList(struct node **head)
{
	struct node *temp;
	int numberOfNodes = 1;
	temp = *head;
	if(temp == NULL)
	{
		printf("List is empty");
		return 0;
	}

	while(temp->next != NULL)
	{
		temp = temp->next;
		numberOfNodes++;
	}

	return (numberOfNodes - 1);
}

void funct(struct node **head, int k)
{
	int index = CountNodesInList(head);
	if (k <= index) {
        for (int i = k; i > 0; --i) {
           DeleteNodeFromList(head, index);
		   --index;
        }
    }
}

void delete(struct node **head) {
	struct node *temp;
	temp = *head;

	while (temp != NULL) {
		temp = temp->next;
	}
	*head = temp;
}

void print_help() {
	printf("Menu:\n");
	printf("1 - add elem\n");
	printf("2 - delete elem\n");
	printf("3 - print\n");
	printf("4 - count of elems\n");
	printf("5 - function\n");
	printf("6 - exit\n");
	printf("7 - help\n");
	printf("8 - delete list\n");
}

int main()
{
	struct node *head = malloc(sizeof(struct node));
	int cmd;
	print_help();
	int index, index1;
	int value, value1, value2;
	int work = 1;

	while (work && scanf("%d", &cmd) == 1) {
		switch(cmd) {
			case 1:
				printf("number of elem: ");
				scanf("%d", &index);
				printf("value of elem: ");
				scanf("%d", &value);
				AddNode(&head, index, value);
				break;
			case 2:
				printf("number of elem: ");
				scanf("%d", &index1);
				DeleteNodeFromList(&head, index1);
				break;
			case 3:
				printf("List: ");
				PrintList(&head);
				break;
			case 4:
				printf("Count of nodes = %d", CountNodesInList(&head));
				printf("\n");
				break;
			case 5:
				printf("enter value: ");
				scanf("%d", &value);
				funct(&head, value);
				break;  
			case 6:
				work = false;
				break;
			case 7:
				print_help();
				break; 
			case 8:
				delete(&head);  
		}
	}
	return 0;
}