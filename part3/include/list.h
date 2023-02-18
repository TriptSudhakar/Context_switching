#ifndef LIST_H
#define LIST_H
/*! 
	@brief Doubly linked list.
*/
struct list {
	struct listentry* head; ///< Head of the linked list. Head is NULL when list is empty.
	struct listentry* tail; ///< Tail of the linked list. Tail is NULL when list is empty.
};

/*! 
	@brief Elements of the Linked List.
*/
struct listentry {
	void *data; ///< Pointer of the data of the listentry
	struct listentry *prev; ///< Pointer of the previous element of the linked list
	struct listentry *next; ///< Pointer of the next element of the linked list
};

/*! 
	@brief Removes the given element from the Linked List 
	@param l : pointer to the linked list.
	@param e : pointer to the linked list entry need to be removed.

	Removes the given element from the Linked List by iterating through it and removing when found.
*/
void list_rm(struct list* l, struct listentry* e);    // Remove an item from the list

/*! 
	@brief Adds the given element to the Linked List 
	@param l : Pointer to the linked list.
	@param data : Element that needs to be added.

	Creates an object of type listentry with its data as the given input and adds it to the end of the list.
*/
struct listentry* list_add(struct list* l, void* data);  // Add an item to the list

/*! 
	@return Returns pointer to a dynamically allocated Linked List.
*/
struct list* list_new();  // Return an initialized list

/*! 
	@param l : Pointer to a linked list.
	@return Returns 1 if List is empty and 0 otherwise.
*/
int is_empty(struct list* l);  // Check if list is empty or not
#endif
