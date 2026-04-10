#include "htab_internal.h"

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