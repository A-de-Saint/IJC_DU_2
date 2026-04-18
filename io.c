#include <stdio.h>
#include <stdlib.h>
#include <type.h> //pro isspace()
#include "htab.h"

//funkce cte jedno slovo (non-space charaktery oddelene space charaktery)
int read_word(unsigned max, char s[max], FILE *f)
{
	unsigned count = 0; //pocet prectenych znaku
	int ch;
	while(true)
	{
		ch = fgetc(f);

		if (ch == EOF)
		{
			//jestlize byl precten pouze EOF, je konec souboru
			if (count == 0)
				return EOF;
			break; //jinak bylo ulozeno jeste slovo
		}

		if (isspace(ch))
		{
			//jestlize nebylo nic precteno, nebylo nic ulozeno (pripad dvou mezer za sebou napr.)
			//tudiz pokracujeme
			if (count == 0)
				continue;
			break;
		}

		//jestlize je jeste misto, ulozit
		if (count < max - 1)
			s[count] = ch;

		count++;
	}

	//nul terminace
	if (count < max - 1)
		s[count] = '\0';
	else
		s[max-1] = '\0';

	return count;
}
		

		

