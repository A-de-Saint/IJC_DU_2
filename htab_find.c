#include "htab_internal.h"

htab_pair_t *htab_find(const htab_t *t, htab_key_t key)
{
	size_t h = htab_hash_function(key);
	size_t idx = h % t->arr_size;
	struct htab_item *item = t->arr[idx];
	while (item != NULL)
	{
		if (strcmp(item->pair.key, key) == 0)
			return &item->pair;
		item = item->next;
	}
	return NULL;
}