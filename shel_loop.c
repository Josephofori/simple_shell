#include "simshell.h"

/**
 * without_comment - deletes comments from input
 *
 * @inp: input
 * Return: input not having comments
 */
char *without_comment(char *inp)
{
	int i, up_to;

	up_to = 0;
	for (i = 0; inp[i]; i++)
	{
		if (inp[i] == '#')
		{
			if (i == 0)
			{
				free(inp);
				return (NULL);
			}

			if (inp[i - 1] == ' ' || inp[i - 1] == '\t' || inp[i - 1] == ';')
				up_to = i;
		}
	}

	if (up_to != 0)
	{
		inp = _reloc(inp, i, up_to + 1);
		inp[up_to] = '\0';
	}

	return (inp);
}

/**
 * shel_loop - shell loop
 * @datash: relevant data (av, input, args)
 *
 * Return: none.
 */
void shel_loop(data_shel *datash)
{
	int lop, i_eof;
	char *input;

	lop = 1;
	while (lop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = read_inline(&i_eof);
		if (i_eof != -1)
		{
			input = without_comment(input);
			if (input == NULL)
				continue;

			if (check_error_syntax(datash, input) == 1)
			{
				datash->stat = 2;
				free(input);
				continue;
			}
			input = repl_var(input, datash);
			lop = split_command(datash, input);
			datash->count += 1;
			free(input);
		}
		else
		{
			lop = 0;
			free(input);
		}
	}
}
