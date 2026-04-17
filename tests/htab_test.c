#include <stdio.h>
#include <assert.h>
#include "../htab.h"

void func(htab_pair_t *data)
{
	printf("Key: %s\tValue: %u\n", data->key, data->value);
}

int main(void)
{
	htab_t *ht = htab_init(100);
	assert(ht != NULL);
	assert(htab_size(ht) == 0);
	printf("Bucket_count: %zu\n", htab_bucket_count(ht));
	assert(htab_bucket_count(ht) == 100);
	assert(htab_find(ht, "a") == NULL);
	
	htab_pair_t *pair = NULL;
	char str[3] = {'a', 'b', '\0'};
	for (int i = 0; i < 10; i++)
	{
		pair = htab_lookup_add(ht, &str[0]);
		assert(pair != NULL);
		assert(strcmp(pair->key, str) == 0);
		assert(pair->value == 1);
		str[0]++;
		str[1]++;
	}

	assert(htab_size(ht) == 10);
	printf("bucket_count: %zu\n", htab_bucket_count(ht));

	str[0] = 'a';
	str[1] = 'b';
	for (int i = 0; i < 10; i++)
	{
		pair = htab_lookup_add(ht, &str[0]);
		assert(pair != NULL);
		assert(strcmp(pair->key, str) == 0);
		assert(pair->value == 2);
		str[0]++;
		str[1]++;
	}

	printf("bucket_count: %zu\n", htab_bucket_count(ht));
	assert(htab_size(ht) == 10);

	str[0] = 'a';
	str[1] = 'b';
	for (int i = 0; i < 10; i++)
	{
		pair = htab_find(ht, &str[0]);
		assert(pair != NULL);
		assert(strcmp(pair->key, str) == 0);
		assert(pair->value == 2);
		str[0]++;
		str[1]++;
	}
	
	str[0] = 'a';
	str[1] = 'b';
	assert(htab_erase(ht, &str[0]));
	assert(htab_size(ht) == 9);
	
	htab_clear(ht);
	assert(htab_size(ht) == 0);
	assert(htab_bucket_count(ht) == 100);

	str[0] = 'a';
	str[1] = 'b';
	for (int i = 0; i < 10; i++)
	{
		pair = htab_lookup_add(ht, &str[0]);
		assert(pair != NULL);
		assert(strcmp(pair->key, str) == 0);
		assert(pair->value == 1);
		str[0]++;
		str[1]++;
	}
	
	htab_for_each(ht, func);
	
	htab_free(ht);
	
	printf("Success!!\n");

	return 0;
}

