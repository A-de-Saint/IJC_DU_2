#include "htab_internal.h"

void htab_clear(htab_t *t)
{
	//odstraneni (uvolneni) vsech prvku
	for (size_t i = 0; i < t->arr_size; i++)
	{
		struct htab_item *item = t->arr[i];
		while (item)
		{
			struct htab_item *next_item = item->next;
			free_item(item);
			item = next_item;
		}
		t->arr[i] = NULL;
	}
	t->size = 0;
}