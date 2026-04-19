// htab_for_each.c
// Řešení příkladu IJC-DU2, příklad b), 17.4.2026
// Autor: Antonín Hrnčíř, FIT
// Přeloženo: gcc 15.2.1
// Implementace funkce htab_for_each pro libhtab

#include "htab_internal.h"

void htab_for_each(const htab_t *t, void (*f)(htab_pair_t *))
{
 	for (size_t i = 0; i < t->arr_size; i++)
	{
		struct htab_item *item = t->arr[i];
		while (item)
		{
			f(&item->pair); //provedeni funkce nad kazdou polozkou
			item = item->next;
		}
	}
}

