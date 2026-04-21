// htab_find.c
// Řešení příkladu IJC-DU2, příklad b), 17.4.2026
// Autor: Antonín Hrnčíř, FIT
// Přeloženo: gcc 15.2.1
// Implementace funkce htab_size pro libhtab

#include "htab_internal.h"

//jednoduse vraci .size
size_t htab_size(const htab_t *htab)
{
	return htab->size;
}
