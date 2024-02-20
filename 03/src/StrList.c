#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "StrList.h"

typedef struct _StrNode {
	char *data;				// the string contained by the node, the memory is "owned" by this node
	struct _StrNode *next;	// the next node in the list
} StrNode;

/**
 * Creates a new StrNode and copies the data into it
 * The allocated data inside the node is owned by the node and should only be freed by it
 * Make sure to call StrNode_free
*/
StrNode *StrNode_create(const char *data)
{
	StrNode *result = malloc(sizeof(StrNode));	// allocate memory for the node
	if (!result) return NULL;					// cheack for malloc fail
	result->data = malloc(strlen(data) + 1);	// allocate memory for node's data (as much as needed including null terminator)
	if (!result->data)		// check for malloc fail
	{
		free(result);		// prevent memory leak
		return NULL;
	}
	strcpy(result->data, data);		// copy the data into the new memory
	result->next = NULL;			// set next to NULL (new node)
	return result;					// return the created node
}

/**
 * Frees the node and its inner data
*/
void StrNode_free(StrNode *node)
{
	if (node == NULL) return;
	free(node->data);	// free the allocated data inside
	free(node);			// free the node itself
}

/**
 * A struct for a list of strings
*/
typedef struct _StrList {
	StrNode *head;	// the first node in the list
	size_t len;		// the number of nodes, useful for various operations and cheap to maintain
} StrList;

/*
 * Allocates a new empty StrList.
 * It's the user responsibility to free it with StrList_free.
 */
StrList *StrList_alloc()
{
	StrList *result = malloc(sizeof(StrList));	// allocate memory for the structure
	if (!result) return NULL;		// check for malloc fail
	result->head = NULL;	// initially no head
	result->len = 0;		// and length 0
	return result;			// return created list
}

/*
	Given a list, remove all elements, also frees them to prevent memory leak
*/
void StrList_removeAll(StrList *list)
{
	assert(list);						// make sure not passed NULL
	while (list->head)					// while there are elements in the list
	{
		StrNode *removed = list->head;	// save the node about to be removed
		list->head = removed->next;		// remove it by setting the next one as the head
		StrNode_free(removed);			// free the old head
	}
	list->len = 0;						// reset length to 0
}

/*
 * Frees the memory and resources allocated to StrList, including all nodes
 * If StrList==NULL does nothing (same as free).
 */
void StrList_free(StrList *list)
{
	if (list == NULL) return;	// skip for NULL
	StrList_removeAll(list);	// remove all elements (also frees their allocated memory)
	free(list);					// free the list structure memory
}

/*
 * Returns the number of elements in the StrList.
 */
size_t StrList_size(const StrList *list)
{
	assert(list);		// make sure not passed NULL
	return list->len;	// return the length
}

/*
 * Inserts an element in the end of the StrList.
 */
void StrList_insertLast(StrList *list, const char *data)
{
	assert(list);		// make sure not passed NULL
	if (list->head == NULL)	// if list is empty need to insert as head
	{
		list->head = StrNode_create(data);	// create the new node with the data
		list->len += 1;		// set new length
		return;		// we're done
	}
	StrNode *p = list->head;	// find last node by starting at head
	while (p->next)				// while has next (i.e. not the last)
	{
		p = p->next;			// move to next
	}
	p->next = StrNode_create(data);	// set the next of p (which is the last) to the newly created node
	list->len += 1;					// increment the size
}

/*
* Inserts an element at given index
*/
void StrList_insertAt(StrList *list, const char *data, int index)
{
	assert(list && index <= (int) list->len);	// make sure not passed NULL and will be able to find index (including one after the end)
	if (index == 0)								// if is the new head
	{
		StrNode *new = StrNode_create(data);	// create new node with data
		assert(new);							// make sure didn't fail
		new->next = list->head;					// the next node is the old head (since it is inserted before it)
		list->head = new;						// the new is the new head
		list->len += 1;							// increment length
		return;									// we're done
	}
	StrNode *p = list->head;		// find the node before the index
	while (index > 1)				// while the target is more than 1 away (not the next node)
	{
		p = p->next;				// move forward
		index -= 1;					// decrement target distance
	}
	StrNode *new = StrNode_create(data);	// create new node
	new->next = p->next;					// set its next to the next of the one before it
	p->next = new;							// set it as the next of the one before it
	list->len += 1;							// increment list length
}

/*
 * Returns the StrList first data.
 */
char *StrList_firstData(const StrList *list)
{
	assert(list && list->len > 0);	// make sure list is not NULL and there is a node
	return list->head->data;		// return the first node's data
}

/*
 * Prints the StrList to the standard output.
 */
void StrList_print(const StrList *list)
{
	assert(list);		// make sure not passed NULL
	if (list->len == 0) // on empty list
	{
		printf("\n");	// print only line break
		return;			// and exit
	}
	printf("%s", list->head->data);	// print first string without space
	for (StrNode *p = list->head->next; p; p = p->next)	// iterate through the rest of the list
		printf(" %s", p->data);						// print each data with a space before
	printf("\n");									// print line end
}

/*
 Prints the word at the given index to the standard output.
*/
void StrList_printAt(const StrList *list, int index)
{
	assert(list && index < (int) list->len);	// make sure not passed NULL and index is inside list
	StrNode *p = list->head;	// look for the node
	while (index > 0)			// while it is more than 0 away
	{
		p = p->next;			// go to next node
		index -= 1;				// decrement distance to the targert
	}
	printf("%s\n", p->data);	// print the node's data
}

/*
 * Return the amount of chars in the list.
*/
int StrList_printLen(const StrList *list)
{
	assert(list);		// make sure not passed NULL
	size_t result = 0;	// itialize result
	for (StrNode *p = list->head; p; p = p->next)	// iterate through the list
		result += strlen(p->data);					// add each node's data's length to result
	return result;		// return the calculated result
}

/*
Given a string, return the number of times it exists in the list.
*/
int StrList_count(StrList *list, const char *data)
{
	assert(list);		// make sure not passed NULL
	size_t result = 0;		// itialize result
	for (StrNode *p = list->head; p; p = p->next)	// iterate through the list
		if (strcmp(p->data, data) == 0) result += 1;	// if data is what we're looking for increment result
	return result;		// return the calculated result
}

/*
	Given a string and a list, remove all the appearences of this string in the list.
*/
void StrList_remove(StrList *list, const char *data)
{
	assert(list);	// make sure not passed NULL
	if (list->len == 0) return;		// if no nodes we're done
	while (list->head && strcmp(list->head->data, data) == 0)	// while there are nodes and the first one is what we're looking for
	{
		StrNode *removed = list->head;		// remove the head same as removeAt with index 0
		list->head = removed->next;
		StrNode_free(removed);
		list->len -= 1;
	}
	if (!list->head) return;				// we emptied the list
	for (StrNode *p = list->head; p; p = p->next)	// iterate through all other nodes
		while (p->next && strcmp(p->next->data, data) == 0)		// while there is a next node and it is what we're looking for
		{
			StrNode *removed = p->next;		// remove the next
			p->next = removed->next;
			StrNode_free(removed);
			list->len -= 1;
		}
}

/*
	Given an index and a list, remove the string at that index.
*/
void StrList_removeAt(StrList *list, int index)
{
	assert(list && index < (int) list->len);	// make sure not passed NULL and index is inside list
	if (index == 0)								// if need to remove head
	{
		StrNode *removed = list->head;			// save the removed node's lcoation
		list->head = removed->next;				// set its next as the head
		StrNode_free(removed);					// free it
		list->len -= 1;
		return;
	}
	StrNode *p = list->head;	// find node before target
	while (index > 1)
	{
		p = p->next;
		index -= 1;
	}
	StrNode *removed = p->next;		// save the removed node's location
	p->next = removed->next;		// remove it from the chain
	StrNode_free(removed);			// free it
	list->len -= 1;
}

/*
 * Checks if two StrLists have the same elements
 * returns 0 if not and any other number if yes
 */
int StrList_isEqual(const StrList *list1, const StrList *list2)
{
	assert(list1 && list2);		// make sure not passed NULL
	if (list1->len != list2->len) return FALSE;		// if lengths are different they are definitely not eqaul
	StrNode *p1 = list1->head;	// go throgh both lists
	StrNode *p2 = list2->head;	// in sync
	while (p1 && p2)	// should become NULL at the same, only && for readability
	{
		if (strcmp(p1->data, p2->data) != 0) return FALSE;	// if the data is not the same at some position they are not equal
		p1 = p1->next;	// move both next
		p2 = p2->next;
	}
	return TRUE;	// if went through whole list they are equal
}

/*
 * Clones the given StrList. 
 * It's the user responsibility to free it with StrList_free.
 */
StrList *StrList_clone(const StrList *original)
{
	assert(original);	// make sure not passed NULL
	StrList *result = StrList_alloc();	// allocate new list
	if (!result) return NULL;	// check alloc fail
	if (original->len == 0) return result;	// if the original is empty we're done
	result->head = StrNode_create(original->head->data);	// copy the head
	assert(result->head);		// make sure creation didn't fail
	StrNode *on = original->head->next;	// next node from original to copy
	StrNode *nn = result->head;			// last node in new
	while (on)	// while there are more nodes to copy
	{
		nn->next = StrNode_create(on->data);	// create new node with on's data, set it as the next node of nn
		assert(nn->next);	// make sure creation didn't fail
		nn = nn->next;		// move nn forward
		on = on->next;		// move on forward
	}
	result->len = original->len;	// copy the length
	return result;
}

/*
 * Reverses the given StrList.
 */
void StrList_reverse(StrList *list)
{
	assert(list);	// make sure not passed NULL
	if (list->len == 0) return;	// if no elements is it its own reverse
	StrNode *prev = NULL;			// the previous node, i.e. the first node in the reverse, needed at the end, initially NULL to be set as the head's new next
	for (StrNode *p = list->head; p;)	// go through the nodes
	{
		StrNode *next = p->next;	// save the next node
		p->next = prev;				// move the current node to the beginning of the reverse list by setting its next to the head
		prev = p;					// set it as the new head of the reverse
		p = next;					// continue to the saved next
	}
	list->head = prev;				// the new head is the head of the reverse
}

/*
 * Sort the given list in lexicographical order using insertion sort
 * This function moves the pointer to the data, which means that the string ownership is transferred
 * Also, any pointers to nodes become invalidated (their data might have changed)
 * But users shouldn't handle pointers to nodes anyway
 */
void StrList_sort(StrList *list)
{
	assert(list);	// make sure not passed NULL
    if (list->len <= 1) return;	// if up to 1 element, it is already sorted
    
    for (StrNode *insert_location = list->head; insert_location; insert_location = insert_location->next)	// while there is some node to insert to
        for (StrNode *contender = insert_location->next; contender; contender = contender->next)	// search for contender from next node to end
            if (strcmp(contender->data, insert_location->data) < 0)		// if contender is smaller than current holder
			{
                char *temp = insert_location->data;				// swap them
                insert_location->data = contender->data;
                contender->data = temp;
            }
}

/*
 * Checks if the given list is sorted in lexicographical order
 * returns 1 for sorted,   0 otherwise
 */
int StrList_isSorted(StrList *list)
{
	assert(list);	// make sure not passed NULL
	if (list->len == 0) return TRUE;	// if no elements it must be sorted
	for (StrNode *p = list->head; p -> next; p = p->next)	// iterate through nodes that have a next
		if (strcmp(p->data, p->next->data) > 0) return FALSE;	// if higher than next in lexicographical order the list is not sorted
	return TRUE;	// if went through whole list then it is sorted
}

