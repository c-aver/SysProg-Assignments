#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "StrList.h"

typedef struct _StrNode {
	char *data;
	struct _StrNode *next;
} StrNode;

/**
 * Creates a new StrNode and copies the data into it
 * The allocated data inside the node is owned by the node and should only be freed by it
 * Make sure to call StrNode_free
*/
StrNode *StrNode_create(const char *data)
{
	StrNode *result = malloc(sizeof(StrNode));
	if (!result) return NULL;
	result->data = malloc(strlen(data) + 1);
	if (!result->data)
	{
		free(result);
		return NULL;
	}
	strcpy(result->data, data);
	result->next = NULL;
	return result;
}

/**
 * Frees the node and its inner data
*/
void StrNode_free(StrNode *node)
{
	if (node == NULL) return;
	free(node->data);
	free(node);
}

/**
 * A struct for a list of strings
*/
typedef struct _StrList {
	StrNode *head;
	size_t len;
} StrList;

/*
 * Allocates a new empty StrList.
 * It's the user responsibility to free it with StrList_free.
 */
StrList *StrList_alloc()
{
	StrList *result = malloc(sizeof(StrList));
	if (!result) return NULL;
	result->head = NULL;
	result->len = 0;
	return result;
}

/*
	Given a list, remove all elements, also frees them to prevent memory leak
*/
void StrList_removeAll(StrList *list)
{
	assert(list);
	while (list->head)
	{
		StrNode *removed = list->head;
		list->head = removed->next;
		StrNode_free(removed);
	}
	list->len = 0;
}

/*
 * Frees the memory and resources allocated to StrList, including all nodes
 * If StrList==NULL does nothing (same as free).
 */
void StrList_free(StrList *list)
{
	if (list == NULL) return;
	StrList_removeAll(list);
	free(list);
}

/*
 * Returns the number of elements in the StrList.
 */
size_t StrList_size(const StrList *list)
{
	assert(list);
	return list->len;
}

/*
 * Inserts an element in the end of the StrList.
 */
void StrList_insertLast(StrList *list, const char *data)
{
	assert(list);
	if (list->head == NULL)
	{
		list->head = StrNode_create(data);
		list->len += 1;
		return;
	}
	StrNode *p = list->head;
	while (p->next)
	{
		p = p->next;
	}
	p->next = StrNode_create(data);
	list->len += 1;
}

/*
* Inserts an element at given index
*/
void StrList_insertAt(StrList *list, const char *data, int index)
{
	assert(list && index <= (int) list->len);
	if (index == 0)
	{
		StrNode *new = StrNode_create(data);
		assert(new);
		new->next = list->head;
		list->head = new;
		list->len += 1;
		return;
	}
	StrNode *p = list->head;
	while (index > 1)
	{
		p = p->next;
		index -= 1;
	}
	StrNode *new = StrNode_create(data);
	new->next = p->next;
	p->next = new;
	list->len += 1;
}

/*
 * Returns the StrList first data.
 */
char *StrList_firstData(const StrList *list)
{
	assert(list && list->len > 0);
	return list->head->data;
}

/*
 * Prints the StrList to the standard output.
 */
void StrList_print(const StrList *list)
{
	assert(list);
	StrNode *p = list->head;
	while (p)
	{
		printf("%s ", p->data);
		p = p->next;
	}
	printf("\n");
}

/*
 Prints the word at the given index to the standard output.
*/
void StrList_printAt(const StrList *list, int index)
{
	assert(list && index < (int) list->len);
	StrNode *p = list->head;
	while (index > 0)
	{
		p = p->next;
		index -= 1;
	}
	printf("%s\n", p->data);
}

/*
 * Return the amount of chars in the list.
*/
int StrList_printLen(const StrList *list)
{
	assert(list);
	size_t result = 0;
	StrNode *p = list->head;
	while (p)
	{
		result += strlen(p->data);
		p = p->next;
	}
	return result;
}

/*
Given a string, return the number of times it exists in the list.
*/
int StrList_count(StrList *list, const char *data)
{
	assert(list);
	int result = 0;
	StrNode *p = list->head;
	while (p)
	{
		if (strcmp(p->data, data) == 0) result += 1;
		p = p->next;
	}
	return result;
}

/*
	Given a string and a list, remove all the appearences of this string in the list.
*/
void StrList_remove(StrList *list, const char *data)
{
	assert(list);
	if (list->len == 0) return;
	while (list->head && strcmp(list->head->data, data) == 0)
	{
		StrNode *removed = list->head;
		list->head = removed->next;
		StrNode_free(removed);
		list->len -= 1;
	}
	StrNode *p = list->head;
	while (p->next)
	{
		while (p->next && strcmp(p->next->data, data) == 0)
		{
			StrNode *removed = p->next;
			p->next = removed->next;
			StrNode_free(removed);
			list->len -= 1;
		}
		p = p->next;
	}
}

/*
	Given an index and a list, remove the string at that index.
*/
void StrList_removeAt(StrList *list, int index)
{
	assert(list && index < (int) list->len);
	if (index == 0)
	{
		StrNode *removed = list->head;
		list->head = removed->next;
		StrNode_free(removed);
		list->len -= 1;
		return;
	}
	StrNode *p = list->head;
	while (index > 1)
	{
		p = p->next;
		index -= 1;
	}
	StrNode *removed = p->next;
	p->next = removed->next;
	StrNode_free(removed);
	list->len -= 1;
}

/*
 * Checks if two StrLists have the same elements
 * returns 0 if not and any other number if yes
 */
int StrList_isEqual(const StrList *list1, const StrList *list2)
{
	assert(list1 && list2);
	if (list1->len != list2->len) return FALSE;
	StrNode *p1 = list1->head;
	StrNode *p2 = list2->head;
	while (p1)
	{
		if (strcmp(p1->data, p2->data) != 0) return FALSE;
		p1 = p1->next;
		p2 = p2->next;
	}
	return TRUE;
}

/*
 * Clones the given StrList. 
 * It's the user responsibility to free it with StrList_free.
 */
StrList *StrList_clone(const StrList *original)
{
	assert(original);
	StrList *result = StrList_alloc();
	if (!result) return NULL;
	if (original->len == 0) return result;
	result->head = StrNode_create(original->head->data);
	StrNode *on = original->head->next;	// next node from original to copy
	StrNode *nn = result->head;			// last node in new
	while (on)
	{
		nn = nn->next = StrNode_create(on->data);	// create new node with on's data, set it as the next node of nn, and move nn forward to it
		on = on->next;		// move on forward
	}
	result->len = original->len;
	return result;
}

/*
 * Reverses the given StrList.
 */
void StrList_reverse(StrList *list)
{
	assert(list);
	if (list->len == 0) return;
	StrNode *prev = NULL;			// the previous node, i.e. the first node in the reverse
	StrNode *curr = list->head;	// the current node being moved to the reverse list
	StrNode *next = NULL;			// the next node
	while (curr)
	{
		next = curr->next;			// set the next
		curr->next = prev;			// change the current to the beginning of the reverse list by setting its next to the head
		prev = curr;				// set curr to the new head of the reverse
		curr = next;				// move curr to the next
	}
	list->head = prev;			// the new head is the head of the reverse
}

/*
 * Sort the given list in lexicographical order 
 */
void StrList_sort(StrList *list)
{
	(void) list;
	assert(FALSE && "unimplemented");	// TODO
}

/*
 * Checks if the given list is sorted in lexicographical order
 * returns 1 for sorted,   0 otherwise
 */
int StrList_isSorted(StrList *list)
{
	assert(list);
	if (list->len == 0) return TRUE;
	StrNode *p = list->head;
	while (p->next)
	{
		if (strcmp(p->data, p->next->data) > 0) return FALSE;
		p = p->next;
	}
	return TRUE;
}

