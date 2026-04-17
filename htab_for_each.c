#include "htab_internal.h"

void htab_for_each(const htab_t *t, void (*f)(htab_pair_t *))
{
 	for (size_t i = 0; i < t->arr_size; i++)
	{
		struct htab_item *item = t->arr[i];
		while (item)
		{
			f(&item->pair);
			item = item->next;
		}
	}
}

