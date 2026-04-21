// htab_internal.h
// Řešení příkladu IJC-DU2, příklad b), 17.4.2026
// Autor: Antonín Hrnčíř, FIT
// Přeloženo: gcc 15.2.1
// Vnitřní (skryté) rozhraní pro libhtab

#ifndef HTAB_INTERNAL_H_
#define HTAB_INTERNAL_H_

#include "htab.h"
#include <stdlib.h> //pro size_t

/* DEKLARACE ENCAPSULATED STRUKTUR */

//struktura htab
struct htab {
    size_t size;
    size_t arr_size;
    struct htab_item *arr[];
};

//struktura htab_item
struct htab_item {
    struct htab_item *next;
    struct htab_pair pair;
};

//pomocna inline funkce pro uvolneni jedne polozky z tabuly
static inline void free_item(struct htab_item *item)
{
	if (!item)
		return;
	if (item->pair.key)
		free((void *)item->pair.key);
	free(item);
}

#endif
