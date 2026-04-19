// htab_hash_function.c
// Řešení příkladu IJC-DU2, příklad b), 17.4.2026
// Autor: Antonín Hrnčíř, FIT
// Přeloženo: gcc 15.2.1
// Implementace funkce htab_hash_function pro libhtab, přesně podle zadání

#include "htab_internal.h"
#include <stdint.h> //pro vynuceni 32bit uint

size_t htab_hash_function(const char *str)
{
	uint32_t h = 0;
	const unsigned char *p;
	for (p = (const unsigned char*)str; *p != '\0'; p++)
		h = 65599 * h + *p;
	return h;
}
