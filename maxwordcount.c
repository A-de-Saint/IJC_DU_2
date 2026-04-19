// maxwordcount.c
// Řešení příkladu IJC-DU2, příklad b), 18.4.2026
// Autor: Antonín Hrnčíř, FIT
// Přeloženo: gcc 15.2.1
// Implementace výpočtu maximálních výskytů slov na standardním vstupu pomocí htab

#include <stdio.h>
#include <stdlib.h>
#include "htab.h"

#define WORD_CHAR_LIMIT 99

#ifdef MY_HASH_FUNCTION
#include <stdint.h>

//vlastni hash funkce (DJB2)
size_t htab_hash_function(const char *str)
{
	uint32_t hash = 5381;
	int c;
	while ((c = *str++))
	{
		hash = ((hash << 5) + hash) + c;
	}
	return hash;
}

#endif

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
	/*
		Číslo 131072 jsem zvolil proto, že na Merlinovi je
		počet slov v /usr/share/dict/words 104334
		(zjištěno pomocí 'wc -l /usr/share/dict/words') a
		131072 je mocnina dvou, která nechává nějakou rezervu i pro
		systémy s vyšším počtem unikátních slov v daném slovníku
		a udržuje load factor hashovací tabulky na hodnotě ~1
	*/
	htab_t *m = htab_init(131072);

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

	htab_free(m);

	return 0;
}



