#include "htab_internal.h"

size_t htab_size(const htab_t *htab)
{
	if (!htab)
		return 0;
	else
		return htab->size;
}