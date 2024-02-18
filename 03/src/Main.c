#include <ctype.h>
#include <stdio.h>
#include "StrList.h"

/**
 * Reads an arbitrary size string from stdin
 * This function allocates memory which must be freed after use
*/
char *input_str(void)
{
	// we will set up a dynamic array inside result with capacity and size
	size_t cap = 1, size = 0;
	char *result = calloc(cap, sizeof(char));	// initial allocation
	if (!result) return NULL;	// failed to calloc
	char c = getchar();			// get first character
	while (c != EOF && !isspace(c))		// while character is not whitespace
	{
		if (size >= cap - 1)	// make sure there is space for the new character
								// -1 for the null terminator we will insert at the end
		{
			cap *= 2;		// double capacity
			result = reallocarray(result, cap, sizeof(char));	// realloc the array with new capacity
			if (!result) return NULL;	// failed to reallocarray
		}
		result[size++] = c;	// add the character to the end and increment size

		c = getchar();		// get next character
	}
	result[size] = '\0';	// add null terminator at the end
	return result;			// return the result
}

/**
 * Reads a sequence of strings from stdin and pushes them into the end of the list
*/
void input_to_list(StrList *list)
{
	size_t n;
	scanf("%zu", &n);		// TODO: should be inputted with `A`?
	size_t prev_len = StrList_size(list);
	while (StrList_size(list) < prev_len + n)
	{
		char *word = input_str();
		if (!word)
		{
			fprintf(stderr, "Failed to allocate memory for word");
			exit(1);
		}
		if (word[0]) StrList_insertLast(list, word);		// this will copy the word so no danger in freeing it after
		free(word);							// free the inputted word
	}
}

int main(void)
{
	int quit = FALSE;
	StrList *list = StrList_alloc();	// allocate the main operational list
	if (!list)	// check alloc fail
	{
		fprintf(stderr, "Failed to allocate list");
		exit(1);
	}
	int action;
	do
	{
		size_t index;			// two variables for various operations
		char *word;
		scanf("%d", &action);	// get the new operation
		switch (action)
		{
		case 1:		// insert strings to list
			input_to_list(list);
			break;
		case 2:		// insert string at specified index
			scanf("%zu", &index);	// input insert index
			word = input_str();		// input string
			if (word[0]) StrList_insertAt(list, word, index);	// insert it
			free(word);		// free the allocated memory
			break;
		case 3:		// print the list
			StrList_print(list);
			break;
		case 4:		// print list length
			printf("%zu\n", StrList_size(list));
			break;
		case 5:		// print string at specified index
			scanf("%zu", &index);	// input index
			StrList_printAt(list, index);
			break;
		case 6:		// print total number of characters in the list
			printf("%d\n", StrList_printLen(list));
			break;
		case 7:		// print how many occurences of a string
			word = input_str();		// input string
			if (word[0]) printf("%d\n", StrList_count(list, word)); // print number of occurences
			free(word);		// free the allocated memory
			break;
		case 8:		// remove all occurences of string in list
			word = input_str();		// input string
			if (word[0]) StrList_remove(list, word);	// remove occurences
			free(word);		// free the allocated memory
			break;
		case 9:		// remove string at specified index
			scanf("%zu", &index);	// input the index
			StrList_removeAt(list, index);	// remove the string
			break;
		case 10:	// reverse the list
			StrList_reverse(list);
			break;
		case 11:	// clear the list
			StrList_removeAll(list);
			break;
		case 12:	// sort the list
			StrList_sort(list);
			break;
		case 13:	// check if list is sorted
			printf("%s\n", StrList_isSorted(list) ? "List is sorted" : "List is not sorted");		// TODO: format?
			break;
		case 0:		// quit
			quit = TRUE;
			break;
		default:
			fprintf(stderr, "Uknown action: %d", action);
			exit(1);
		}
	} while (!quit);

	StrList_free(list);		// free the operational list

	return 0;
}
