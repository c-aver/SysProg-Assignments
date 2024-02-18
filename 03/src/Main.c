#include <ctype.h>
#include <stdio.h>
#include "StrList.h"

// this function allocates space which must be freed after using
char *input_str(void)
{
	size_t curr_cap = 1, curr_size = 0;
	char *result = calloc(curr_cap, sizeof(char));
	if (!result) return NULL;
	char c = getchar();
	while (c != EOF && !isspace(c))
	{
		if (curr_size >= curr_cap - 1)	// make sure there is space for the new character, -1 for null terminator we will insert at the end
		{
			curr_cap *= 2;		// double capacity
			result = reallocarray(result, curr_cap, sizeof(char));	// realloc the array with new capacity
			if (!result) return NULL;
		}
		result[curr_size++] = c;	// add it to the end and increment size

		c = getchar();				// get a new character
	}
	result[curr_size] = '\0';
	return result;
}

void input_to_list(StrList *list)
{

	size_t n;
	scanf("%zu ", &n);
	for (size_t i = 0; i < n; ++i)
	{
		char *word = input_str();
		if (!word)
		{
			fprintf(stderr, "Failed to allocate memory for word");
			exit(1);
		}
		StrList_insertLast(list, word);		// this will copy the word so no danger in freeing it after
		free(word);
	}
}

int main(void)
{
	int quit = FALSE;
	int action;
	StrList *list = StrList_alloc();
	if (!list)
	{
		fprintf(stderr, "Failed to allocate list");
		exit(1);
	}
	do
	{
		size_t index;
		char word[MAX_STR_LEN];
		scanf("%d", &action);
		switch (action)
		{
		case 1:
			input_to_list(list);
			break;
		case 2:
			scanf("%zu %s", &index, word);
			StrList_insertAt(list, word, index);
			break;
		case 3:
			StrList_print(list);
			break;
		case 4:
			printf("%zu\n", StrList_size(list));
			break;
		case 5:
			scanf("%zu", &index);
			StrList_printAt(list, index);
			break;
		case 6:
			printf("%d\n", StrList_printLen(list));
			break;
		case 7:
			scanf("%s", word);
			printf("%d\n", StrList_count(list, word));
			break;
		case 8:
			scanf("%s", word);
			StrList_remove(list, word);
			break;
		case 9:
			scanf("%zu", &index);
			StrList_removeAt(list, index);
			break;
		case 10:
			StrList_reverse(list);
			break;
		case 11:
			StrList_removeAll(list);
			break;
		case 12:
			StrList_sort(list);
			break;
		case 13:
			printf("%s\n", StrList_isSorted(list) ? "List is sorted" : "List is not sorted");		// TODO: format?
			break;
		case 0:
			quit = TRUE;
		}
	} while (!quit);
	StrList_free(list);

	return 0;
}
