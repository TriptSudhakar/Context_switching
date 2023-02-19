#include<stdlib.h>
#include<stdio.h>
struct list {
	struct listentry* head;
	struct listentry* tail;
};

struct listentry {
	void *data;
	struct listentry *prev;
	struct listentry *next;
};

void list_rm(struct list* l, struct listentry* e)
{
	if (e==NULL) return;
	else if (l->head == e && l->tail == e)
	{
		l->head = l->tail = NULL;
	}
	else if(l->head == e)
	{
		l->head = e->next;
		e->next->prev = NULL;
	}
	else if(l->tail == e)
	{
		l->tail = e->prev;
		e->prev->next = NULL;
	}
	else 
	{
		e->prev->next = e->next;
		e->next->prev = e->prev;
	}
	free(e);
};    // Remove an item from the list
struct listentry* list_add(struct list* l, void* data)
{
	if(l->head == NULL)
	{
		struct listentry* temp = (struct listentry*) malloc(sizeof(struct listentry));
		temp->data = data;
		temp->prev = NULL;
		temp->next = NULL;
		l->head = temp;
		l->tail = temp;
		return temp;
	}
	else 
	{
		struct listentry* temp = (struct listentry*) malloc(sizeof(struct listentry));
		temp->data = data;
		temp->prev = l->tail;
		temp->next = NULL;
		l->tail->next = temp;
		l->tail = temp;
		return temp;
	}
};  // Add an item to the list
struct list* list_new()
{
	struct list *l = (struct list*) malloc(sizeof(struct list));
	l->head = l->tail = NULL;
	return l;
};  // Return an initialized list
int is_empty(struct list* l)
{
	if(l->head == NULL) return 1;
	return 0;
};  // Check if list is empty or not
// #endif
