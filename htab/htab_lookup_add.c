#include "htab_internal.h"

htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key)
{	
	size_t h = htab_hash_function(key);
	size_t idx = h % t->arr_size;
	struct htab_item *item = t->arr[idx];
	while (item != NULL)
	{
		if (strcmp(item->pair.key, key) == 0)
			return &item->pair;
		//early exit loopu, aby byl item stale jeste dostupny po loopu
		if (item->next == NULL)
			break;
		item = item->next;
	}
	struct htab_item *new_item = malloc(sizeof(struct htab_item));
	if (new_item)
	{
		t->size++;
		new_item->next = NULL;
	char *key_dup = strdup(key);
		new_item->pair.key = key_dup;
	}
	item->next = new_item;
	return &new_item->pair;
}