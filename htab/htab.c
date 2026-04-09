#include "htab.h"
#include <stdlib.h>

struct htab {
    size_t size;
    size_t arr_size;
    struct htab_item *arr[];
};

struct htab_item {
    struct htab_item *next;
    struct htab_pair;
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

size_t htab_size(htab_t *htab)
{
	if (!htab)
		return 0;
	else
		return htab->size;
}

size_t htab_bucket_count(htab_t *htab)
{
	if (!htab)	
		return 0;
	else
		return htab->arr_size;
}

htab_pair_t *htab_find(htab_t *t, htab_key_t key)
{
	size_t h = htab_hash_function(key);
	size_t idx = h % t->arr_size;
	htab_pair_t *pair = t->arr[idx];
	while (pair != NULL)
	{
		if (strcmp(pair->key, key) == 0)
			return pair;
		pair = pair->next;
	}
	return NULL;
}

htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key)
{	
	size_t h = htab_hash_function(key);
	size_t idx = h % t->arr_size;
	htab_pair_t *pair = t->arr[idx];
	while (pair != NULL)
	{
		if (strcmp(pair->key, key) == 0)
			return pair;
		//early exit loopu, aby byl pair stale jeste dostupny po loopu
		if (pair->next == NULL)
			break;
		pair = pair->next;
	}
	new_pair = malloc(sizeof(htab_pair_t));
	if (new_pair)
	{
		htab->size++;
		new_pair->next = NULL;
		key_dup = strdup(key);
		new_pair->key = key_dup;
	}
	pair->next = new_pair;
	return new_pair;
}

static inline void free_pair(htab_pair_t *pair)
{
	if (!pair)
		return;
	if (pair->key)
		free(pair->key);
	free(pair)
}

bool htab_erase(htab_t *t, htab_key_t key)
{
	size_t h = htab_hash_function(key);
	size_t idx = h % t->arr_size;
	htab_pair_t *prev_pair = NULL;
	htab_pair_t *pair = t->arr[idx];
	while (pair != NULL)
	{
		if (strcmp(pair->key, key) == 0)
			break;
		prev_pair = pair;
		pair = pair->next;
	}
	if (!pair)
		return false;
	//unlinknuti pairu
	if (prev_pair)
		prev_pair->next = pair->next;
	else
		t->arr[idx] = pair->next;
	free_pair(pair);
	t->size--;
	return true;
}

void htab_for_each(htab_t *t, void *func)
{
	//TODO
}

void htab_clear(htab_t *t)
{
	//odstraneni (uvolneni) vsech prvku
	for (size_t i = 0; i < t->arr_size; i++)
	{
		htab_pair *pair = t->arr[i];
		while (pair)
		{
			htab_pair_t *next_pair = pair->next;
			free_pair(pair);
			pair = next_pair;
		}
		t->arr[i] = NULL;
	}
	t->size = 0;
}

void htab_free(htab_t *t)
{
	htab_clear(t);
	free(t)
}

