#include "simshell.h"

/**
 * swap_chars - swaps | and & for non-printed char
 *
 * @input: input
 * @bool: type of swap
 * Return: swap string
 */
char *swap_chars(char *input, int bool)
{
	int a;

	if (bool == 0)
	{
		for (a = 0; input[a]; a++)
		{
			if (input[a] == '|')
			{
				if (input[a + 1] != '|')
					input[a] = 16;
				else
					a++;
			}

			if (input[a] == '&')
			{
				if (input[a + 1] != '&')
					input[a] = 12;
				else
					a++;
			}
		}
	}
	else
	{
		for (a = 0; input[a]; a++)
		{
			input[a] = (input[a] == 16 ? '|' : input[a]);
			input[a] = (input[a] == 12 ? '&' : input[a]);
		}
	}
	return (input);
}

/**
 * add_node - add separators and command lines to lists
 *
 * @head_s: separator list head
 * @head_l: command lines list head
 * @input: input
 * Return: none
 */
void add_node(sep_list **head_s, line_list **head_l, char *input)
{
	int i;
	char *line;

	input = swap_chars(input, 0);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			add_sep_node(head_s, input[i]);

		if (input[i] == '|' || input[i] == '&')
		{
			add_sep_node(head_s, input[i]);
			i++;
		}
	}

	line = _strtak(input, ";|&");
	do {
		line = swap_chars(line, 1);
		add_line_node(head_l, line);
		line = _strtak(NULL, ";|&");
	} while (line != NULL);

}

/**
 * go_nextt - go to next stored command line
 *
 * @list_s: separator list
 * @list_l: command line list
 * @datash: data structure
 * Return: none
 */
void go_nextt(sep_list **list_s, line_list **list_l, data_shel *datash)
{
	int lop_sep;
	sep_list *ls_s;
	line_list *ls_l;

	lop_sep = 1;
	ls_l = *list_l;
	ls_s = *list_s;

	while (ls_s != NULL && lop_sep)
	{
		if (datash->stat == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				lop_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				lop_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !lop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * split_command - split command lines according to
 * the separators ,; | and &, and executes them
 *
 * @datash: data structure
 * @input: input
 * Return: 0 to exit, 1 to continue
 */
int split_command(data_shel *datash, char *input)
{

	sep_list *head_s, *list_s;
	line_list *head_l, *list_l;
	int lop;

	head_s = NULL;
	head_l = NULL;

	add_node(&head_s, &head_l, input);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		datash->input = list_l->line;
		datash->args = split_lines(datash->input);
		lop = exec_inline(datash);
		free(datash->args);

		if (lop == 0)
			break;

		go_nextt(&list_s, &list_l, datash);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_sep_listt(&head_s);
	frees_line_list(&head_l);

	if (lop == 0)
		return (0);
	return (1);
}

/**
 * split_lines - tokenize the input str
 *
 * @input: input str
 * Return: splitted string
 */
char **split_lines(char *input)
{
	size_t bsize;
	size_t i;
	char **tokens;
	char *token;

	bsize = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtak(input, TOK_DELIM);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += TOK_BUFSIZE;
			tokens = _relocdp(tokens, i, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtak(NULL, TOK_DELIM);
		tokens[i] = token;
	}

	return (tokens);
}
