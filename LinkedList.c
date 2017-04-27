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
		
	for(i=0;i<=4;i++){
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
	n->value = i*2;
	if (head == NULL){
		n->ptr = NULL;
		head = n;
		return head;
	}
	n->ptr = head;
	head = n;

	return head;
}

ll* delete_front(ll* head){
	
	ll *ptr;
	if(head == NULL)
	{
		printf("empty, cannot delete");
		return head;
	}
	if (head->ptr == NULL){
		free(head);	
		head = NULL;
		return head;
	}
	ptr = head;
	head= head->ptr;
	free(ptr);
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
		t = t->ptr;
	}
	return 0;
}





