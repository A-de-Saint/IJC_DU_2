#include "htab_internal.h"

void htab_free(htab_t *t)
{
    //vyuziti jiz existujici funkce pro uvolneni vsech polozek
	htab_clear(t);
	free(t);
}