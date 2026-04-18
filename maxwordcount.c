#include <stdio.h>
#include <stdlib.h>
#include "htab.h"

#define WORD_CHAR_LIMIT 99

int read_word(unsigned max, char s[max], FILE *f);

static unsigned max = 0;

void find_max(htab_pair_t *data)
{
	if (data->value > max)
		max = data->value;
}

void print_max(htab_pair_t *data)
{
	if (data->value == max)
		printf("%s\t%u\n", data->key, data->value);
}

int main()
{
	htab_t *m = htab_init(450000);

	char word[WORD_CHAR_LIMIT + 1];
	int res;
	bool warned_already = false; //informace o tom, jestli uz byl uzivatel varovan o moc dlouhem slovu
	while ((res = read_word(sizeof(word), word, stdin)) != EOF)
	{
		if ((size_t)res >= sizeof(word) && !warned_already)
		{
			fprintf(stderr, "Warning: Word(s) longer than %zu found and will be trimmed\n", sizeof(word));
			warned_already = true;
		}

		htab_pair_t *pair = htab_lookup_add(m, word);
		if (!pair)
		{
			fprintf(stderr, "Failed to add '%s' to the hash table\n", word);
		}
	}

	max = 0;
	htab_for_each(m, find_max);

	htab_for_each(m, print_max);

	return 0;
}



