#include "htab_internal.h"

//dela v podstate to same jako strdup (strdup nefunguje na c11)
char *duplicate_string(const char *string)
{
	char *dup = malloc(strlen(string) + 1);
	if (dup)
		strcpy(dup, string);
	return dup;
}

htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key)
{	
	size_t h = htab_hash_function(key);
	size_t idx = h % t->arr_size;
	struct htab_item *item = t->arr[idx];
	while (item != NULL)
	{
		if (strcmp(item->pair.key, key) == 0)
		{
			item->pair.value++;
			return &item->pair;
		}
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
		char *key_dup = duplicate_string(key);
		if (!key_dup)
		{
			free(new_item);
			return NULL;
		}
		new_item->pair.key = key_dup;
		new_item->pair.value = 1;
	}
	else
		return NULL;
	if (item)
		item->next = new_item;
	else 
		t->arr[idx] = new_item;
	return &new_item->pair;
}
