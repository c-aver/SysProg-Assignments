#include <stdio.h>
#include "StrList.h"

void input_list(StrList *list)
{
	size_t n = 10;		// TODO: input this from the user when presses `A`?
	for (size_t i = 0; i < n; ++i)
	{
		char word[MAX_STR_LEN];
		scanf("%s", word);
		StrList_insertLast(list, word);
	}
}

int main(void)
{
	int quit = FALSE;
	int action;
	StrList *list = StrList_alloc();
	do
	{
		size_t index;
		char word[MAX_STR_LEN];
		scanf("%d", &action);
		switch (action)
		{
		case 1:
			input_list(list);
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
			StrList_printLen(list);
			break;
		case 7:
			scanf("%s", word);
			printf("%zu\n", StrList_count(list, word));		// FIXME: wrong type returned
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
			printf("%s", StrList_isSorted(list) ? "List is sorted" : "List is not sorted");
			break;
		case 0:
			quit = TRUE;
		}
	} while (!quit);
	StrList_free(list);

	return 0;
}
