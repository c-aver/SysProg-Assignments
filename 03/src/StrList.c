#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "StrList.h"

typedef struct _StrNode {
	char *data;
	struct _StrNode *next;
} StrNode;

StrNode *StrNode_create(const char *data)
{
	StrNode *result = malloc(sizeof(StrNode));
	if (!result) return NULL;
	result->data = malloc(strlen(data));
	if (!result->data)
	{
		free(result);
		return NULL;
	}
	strcpy(result->data, data);
	result->next = NULL;
	return result;
}

void StrNode_free(StrNode *node)
{
	free(node->data);
	free(node);
}

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
	Given a list, remove all elements
*/
void StrList_removeAll(StrList* StrList)
{
	while (StrList->head)
	{
		StrNode *removed = StrList->head;
		StrList->head = removed->next;
		StrNode_free(removed);
	}
	StrList->len = 0;
}

/*
 * Frees the memory and resources allocated to StrList.
 * If StrList==NULL does nothing (same as free).
 */
void StrList_free(StrList* StrList)
{
	StrList_removeAll(StrList);
	free(StrList);
}

/*
 * Returns the number of elements in the StrList.
 */
size_t StrList_size(const StrList* StrList)
{
	return StrList->len;
}

/*
 * Inserts an element in the end of the StrList.
 */
void StrList_insertLast(StrList* StrList, const char* data)
{
	if (StrList->head == NULL)
	{
		StrList->head = StrNode_create(data);
		StrList->len += 1;
		return;
	}
	StrNode *p = StrList->head;
	while (p->next)
	{
		p = p->next;
	}
	p->next = StrNode_create(data);
	StrList->len += 1;
}

/*
* Inserts an element at given index
*/
void StrList_insertAt(StrList* StrList, const char* data, int index)
{
	assert(index <= (int) StrList->len && "Cannot insert at index larger than end");
	if (index == 0)
	{
		StrNode *new = StrNode_create(data);
		new->next = StrList->head;
		StrList->head = new;
		StrList->len += 1;
		return;
	}
	StrNode *p = StrList->head;
	while (index > 1)
	{
		p = p->next;
		index -= 1;
	}
	StrNode *new = StrNode_create(data);
	new->next = p->next;
	p->next = new;
	StrList->len += 1;
}

/*
 * Returns the StrList first data.
 */
char *StrList_firstData(const StrList* StrList)
{
	return StrList->head->data;
}

/*
 * Prints the StrList to the standard output.
 */
void StrList_print(const StrList* StrList)
{
	StrNode *p = StrList->head;
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
void StrList_printAt(const StrList* StrList, int index)
{
	assert(index < (int) StrList->len && "Cannot print index larger than length");
	StrNode *p = StrList->head;
	while (index > 0)
	{
		p = p->next;
		index -= 1;
	}
	printf("%s", p->data);
}

/*
 * Return the amount of chars in the list.
*/
int StrList_printLen(const StrList* StrList)
{
	size_t result = 0;
	StrNode *p = StrList->head;
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
int StrList_count(StrList* StrList, const char* data)
{
	int result = 0;
	StrNode *p = StrList->head;
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
void StrList_remove(StrList* StrList, const char* data)
{
	while (strcmp(StrList->head->data, data) == 0)
	{
		StrNode *removed = StrList->head;
		StrList->head = removed->next;
		StrNode_free(removed);
		StrList->len -= 1;
	}
	StrNode *p = StrList->head;
	while (p)
	{
		while (strcmp(p->next->data, data) == 0)
		{
			StrNode *removed = p->next;
			p->next = removed->next;
			StrNode_free(removed);
			StrList->len -= 1;
		}
		p = p->next;
	}
}

/*
	Given an index and a list, remove the string at that index.
*/
void StrList_removeAt(StrList* StrList, int index)
{
	assert(index < (int) StrList->len && "Cannot delete index larger than length");
	if (index == 0)
	{
		StrNode *removed = StrList->head;
		StrList->head = removed->next;
		StrNode_free(removed);
		StrList->len -= 1;
		return;
	}
	StrNode *p = StrList->head;
	while (index > 1)
	{
		p = p->next;
		index -= 1;
	}
	StrNode *removed = p->next;
	p->next = removed->next;
	StrNode_free(removed);
	StrList->len -= 1;
}

/*
 * Checks if two StrLists have the same elements
 * returns 0 if not and any other number if yes
 */
int StrList_isEqual(const StrList* StrList1, const StrList* StrList2)
{
	if (StrList1->len != StrList2->len) return FALSE;
	StrNode *p1 = StrList1->head;
	StrNode *p2 = StrList2->head;
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
StrList* StrList_clone(const StrList *original)
{
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
void StrList_reverse(StrList *StrList)
{
	if (StrList->len == 0) return;
	StrNode *prev = NULL;			// the previous node, i.e. the first node in the reverse
	StrNode *curr = StrList->head;	// the current node being moved to the reverse list
	StrNode *next = NULL;			// the next node
	while (curr)
	{
		next = curr->next;			// set the next
		curr->next = prev;			// change the current to the beginning of the reverse list by setting its next to the head
		prev = curr;				// set curr to the new head of the reverse
		curr = next;				// move curr to the next
	}
	StrList->head = prev;			// the new head is the head of the reverse
}

/*
 * Sort the given list in lexicographical order 
 */
void StrList_sort(StrList *StrList)
{
	(void) StrList;
	assert(FALSE && "unimplemented");	// TODO
}

/*
 * Checks if the given list is sorted in lexicographical order
 * returns 1 for sorted,   0 otherwise
 */
int StrList_isSorted(StrList* StrList)
{
	if (StrList->len == 0) return TRUE;
	StrNode *p = StrList->head;
	while (p->next)
	{
		if (strcmp(p->data, p->next->data) > 0) return FALSE;
		p = p->next;
	}
	return TRUE;
}

