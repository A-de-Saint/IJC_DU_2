// htab_bucket_count.c
// Řešení příkladu IJC-DU2, příklad b), 17.4.2026
// Autor: Antonín Hrnčíř, FIT
// Přeloženo: gcc 15.2.1
// Implementace funkce htab_bucket_count pro libhtab

#include "htab_internal.h"

size_t htab_bucket_count(const htab_t *htab)
{
	if (!htab)	
		return 0;
	else
		return htab->arr_size;
}
