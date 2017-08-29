/*
This is doubly link list program with basic operations such as insertion (from front), deletion (from front) and travarsal.

Created By: Vachik Dave
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct linkedlist ll;

struct linkedlist{
	ll *dfwptr;
	ll *bwptr;
	int value;
};


ll* insert_front(ll*,int);
ll* delete_front(ll* head);
int traverse(ll* head);

int main()
{
	int i;
	ll *head = NULL;
		
	for(i=0;i<=10;i++){
		head = insert_front(head,i);
	}
	//printf("hi");
	traverse(head);
	printf("\n");

	for(i=0;i<=5;i++){
		head = delete_front(head);
	}
	traverse(head);
	printf("\n");


	return 0;
}

ll* insert_front(ll* head,int i){
	ll *n;
	n = malloc(sizeof(ll));
	n->value = i;
	n->bwptr = NULL;		
	if (head == NULL){
		n->fwptr = NULL;
		head = n;		
		return head;
	}
	n->fwptr = head;
	head->bwptr = n;
	head = n;
	return head;
}

ll* delete_front(ll* head){
	
	ll *temp;
	if(head == NULL)
	{
		printf("empty, cannot delete");
		return head;
	}
	if (head->fwptr == NULL){
		free(head);	
		head = NULL;
		return head;
	}
	
	temp = head->fwptr;
	free(head);
	temp->bwptr = NULL;
	head = temp;		
	return head;
}

int traverse(ll* head){

	//printf("hi");	
	ll *t;
	t = head;
	if(head == NULL)
		printf("empty \n");
	while(t != NULL){
		printf("%d-",t->value);
		t = t->fwptr;
	}
	return 0;
}





