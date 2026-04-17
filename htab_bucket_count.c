#include "htab_internal.h"

size_t htab_bucket_count(const htab_t *htab)
{
	if (!htab)	
		return 0;
	else
		return htab->arr_size;
}