// htab_free.c
// Řešení příkladu IJC-DU2, příklad b), 17.4.2026
// Autor: Antonín Hrnčíř, FIT
// Přeloženo: gcc 15.2.1
// Implementace funkce htab_free pro libhtab

#include "htab_internal.h"

void htab_free(htab_t *t)
{
    //vyuziti jiz existujici funkce pro uvolneni vsech polozek
	htab_clear(t);
	free(t); //uvolneni samotne alokovane tabulky
}
