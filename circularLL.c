/*
This is circular link list program with basic operations such as insertion (from front), deletion (from front) and travarsal.

Created By: Vachik Dave
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct linkedlist ll;

struct linkedlist{
	ll *ptr;
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
	ll *n,*t;
	t = head;
	n = malloc(sizeof(ll));
	n->value = i;
	if (head == NULL){
		n->ptr = n;
		head = n;
		return head;
	}
	n->ptr = head;
	t = t->ptr;
	while(t->ptr != head){
		t = t->ptr;			
	}
	t->ptr = n;
	head = n;
	return head;
}

ll* delete_front(ll* head){
	
	ll *ptr,*t;
	if(head == NULL)
	{
		printf("empty, cannot delete");
		return head;
	}
	if (head->ptr == head){
		free(head);	
		head = NULL;
		return head;
	}
	t = head;
	while(t->ptr != head){
		t = t->ptr;			
	}
	t->ptr = head->ptr;
	free(head);
	head = t->ptr;
	return head;
}

int traverse(ll* head){

	//printf("hi");	
	ll *t;
	t = head;
	if(head == NULL)
		printf("empty \n");
	printf("%d-",t->value);
	t = t->ptr;
	while(t != head){
		printf("%d-",t->value);
		t = t->ptr;
				
	}
	return 0;
}





