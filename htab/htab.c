#include "htab.h"
#include <stdlib.h>
#include <stdint.h>

struct htab {
    size_t size;
    size_t arr_size;
    struct htab_item *arr[];
};

struct htab_item {
    struct htab_item *next;
    struct htab_pair pair;
};

size_t htab_hash_function(const char *str)
{
	uint32_t h = 0;
	const unsigned char *p;
	for (p = (const unsigned char*)str; *p != '\0'; p++)
		h = 65599 * h + *p;
	return h;
}

htab_t *htab_init(size_t n)
{
    htab_t *new_htab = malloc(sizeof(htab_t) + n * sizeof(struct htab_item*));
    if (!new_htab)
        return NULL;

    new_htab->arr_size = n;
    new_htab->size = 0;

    //nastavit vsechny dalsi prvky seznamu na NULL
    for (size_t i = 0; i < n; i++)
        new_htab->arr[i] = NULL;

    return new_htab;
}

size_t htab_size(const htab_t *htab)
{
	if (!htab)
		return 0;
	else
		return htab->size;
}

size_t htab_bucket_count(const htab_t *htab)
{
	if (!htab)	
		return 0;
	else
		return htab->arr_size;
}

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

static inline void free_item(struct htab_item *item)
{
	if (!item)
		return;
	if (item->pair.key)
		free((void *)item->pair.key);
	free(item);
}

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

void htab_for_each(const htab_t *t, void (*)(htab_pair_t *))
{
 	for (size_t i = 0; i < t->arr_size; i++)
	{
		struct htab_item *item = t->arr[i];
		while (item)
		{
			//TODO	
			item = item->next;
		}
	}

}

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

void htab_free(htab_t *t)
{
	htab_clear(t);
	free(t);
}

