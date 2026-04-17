#include "htab_internal.h"

bool htab_erase(htab_t *t, htab_key_t key)
{
	size_t h = htab_hash_function(key);
	size_t idx = h % t->arr_size;
	struct htab_item *prev_item = NULL;
	struct htab_item *item = t->arr[idx];
	while (item)
	{
		if (strcmp(item->pair.key, key) == 0)
			break;
		prev_item = item;
		item = item->next;
	}
	if (!item)
		return false;
	//unlinknuti itemu
	if (prev_item)
		prev_item->next = item->next;
	else //jestlize prev_item == NULL, maze se prvni polozka seznamu
		t->arr[idx] = item->next;
	free_item(item);
	t->size--;
	return true;
}