// htab_find.c
// Řešení příkladu IJC-DU2, příklad b), 17.4.2026
// Autor: Antonín Hrnčíř, FIT
// Přeloženo: gcc 15.2.1
// Implementace funkce htab_find pro libhtab

#include "htab_internal.h"

htab_pair_t *htab_find(const htab_t *t, htab_key_t key)
{
	size_t h = htab_hash_function(key);
	size_t idx = h % t->arr_size;

	//pruchod vazanym seznamem
	struct htab_item *item = t->arr[idx];
	while (item != NULL)
	{
		if (strcmp(item->pair.key, key) == 0)
			return &item->pair;
		item = item->next;
	}
	return NULL; //pripad, ze se nic nenaslo
}
