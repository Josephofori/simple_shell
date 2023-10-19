#include "simshell.h"

/**
 * read_inline - reads input string.
 *
 * @i_eof: return getline function value
 * Return: input str
 */
char *read_inline(int *i_eof)
{
	char *input = NULL;
	size_t bufsize = 0;

	*i_eof = get_inline(&input, &bufsize, stdin);

	return (input);
}
