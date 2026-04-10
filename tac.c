#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define LINE_CHAR_LIMIT 1024

typedef struct sl_node_t {
    char data[LINE_CHAR_LIMIT + 1];
    struct sl_node_t *next_node;
} SL_Node;

typedef struct {
    SL_Node *first;
} StringList;

void list_init(StringList *sl)
{
    sl->first = NULL;
}

bool list_ins_first(StringList *sl, char *line)
{
    SL_Node *node = malloc(sizeof(SL_Node));

    //kontrola alokace
    if (node == NULL)
    {
        fprintf(stderr, "list_ins_first: Memory allocation failure\n");
        return false;
    }

    //kopirovani s null termination
    strncpy(node->data, line, LINE_CHAR_LIMIT);
    node->data[LINE_CHAR_LIMIT] = '\n';

    //zarazeni do seznamu
    node->next_node = sl->first;
    sl->first = node;

    return true;
}

void list_print(StringList *sl)
{
    SL_Node *node = sl->first;
    while (node != NULL)
    {
        printf("%s\n", node->data);
        node = node->next_node;
    }
}

size_t list_size(StringList *sl)
{
    size_t size = 0;
    SL_Node *node = sl->first;
    while (node != NULL)
    {
        size++;
        node = node->next_node;
    }
    return size;
}

void list_free(StringList *sl)
{
    SL_Node *node = sl->first;
    while (node != NULL)
    {
        SL_Node *tmp = node->next_node;
        free(node);
        node = tmp;
    }
}

//precte jeden radek z file, terminuje '\'
//vraci -1 v pripade chyby ci EOF, jinak pocet charakteru na radku
int read_line(char *buff, size_t buff_size, FILE *file)
{
    int ch;
    size_t i = 0; //pozice v bufferu
    while ((ch = fgetc(file)) != '\n')
    {
        if (ch == EOF)
            break;
        if (i < buff_size - 1)
        {
            buff[i] = ch;
        }
        i++;
    }
    if (ch == EOF && i == 0)
        return -1;
    if (i >= buff_size)
        buff[buff_size - 1] = '\0';
    else 
        buff[i] = '\0';
    return i;
}

bool input_to_list(StringList *sl, FILE *file, int l)
{
    char buff[LINE_CHAR_LIMIT + 1];
    bool no_overflow = true; //aby byl warning vypsan jen jednou
    int res;
	int lines_read = 0;
    while ((res = read_line(buff, sizeof(buff), file)) != -1)
    {
        if (res >= (int)sizeof(buff) && no_overflow)
        {
            fprintf(stderr, "Warning: Line longer than %zu found and will be trimmed\n", sizeof(buff) - 1);
            no_overflow = false;
        }
        if (!list_ins_first(sl, buff))
            return false;
		lines_read++;
		if (l >= 0 && lines_read >= l)
			break;
    }
    return true;
}

int main(int argc, char **argv)
{
    //soubor pro input
    FILE *input = stdin;
	int l = -1; //inicializovano na -1 (pokud -l neni specifikovano)
    bool reading_stdin = true;
    if (argc > 1)
	{	
		//cte vsechny argumenty
		for (int i = 1; i < argc; i++)
		{
			//case '-l' 'cislo'
			if (l < 0 && strcmp(argv[i], "-l") == 0)
			{
				i++;
				if (i >= argc)
				{
					fprintf(stderr, "Missing number after -l\n");
					return 1;
				}
				char *conv_check;
				l = (int)strtoul(argv[i], &conv_check, 10);
				if (!conv_check || *conv_check != '\0')
				{
					fprintf(stderr, "Invalid argument after -l: %s\n", argv[i]);
					return 1;
				}
			}
			else if (reading_stdin) //case 'filename.suff'
			{
				input = fopen(argv[i], "r");
				if (input == NULL)
				{
					fprintf(stderr, "Failed to open %s\n", argv[i]);
					return 1;
				}
				reading_stdin = false;
			}
		}
	}

    //inicializace listu
    StringList sl;
    list_init(&sl);

    //cteni souboru do listu
    bool read_res = input_to_list(&sl, input, l);
    if (!read_res)
    {
        list_free(&sl);
        return 1;
    }

    if (!reading_stdin)
        fclose(input);

    //vypsani listu
    list_print(&sl);
    list_free(&sl);

    return 0;
}
