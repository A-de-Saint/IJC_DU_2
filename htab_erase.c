// htab_erase.c
// Řešení příkladu IJC-DU2, příklad b), 17.4.2026
// Autor: Antonín Hrnčíř, FIT
// Přeloženo: gcc 15.2.1
// Implementace funkce htab_erase pro libhtab

#include "htab_internal.h"

bool htab_erase(htab_t *t, htab_key_t key)
{
	//naleznuti prvku
	size_t h = htab_hash_function(key);
	size_t idx = h % t->arr_size;

	//pro spravne unlinknuti je treba trackovat i predchozi prvek ve vazanem seznamu
	struct htab_item *prev_item = NULL;
	struct htab_item *item = t->arr[idx];

	while (item)
	{
		if (strcmp(item->pair.key, key) == 0)
			break;
		prev_item = item;
		item = item->next;
	}

	//pripad nenaleznuti prvku
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
