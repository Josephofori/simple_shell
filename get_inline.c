#include "simshell.h"

/**
 * bring_inline - assigns line var for get_line
 * @lineptr: Buffer that stores the input str
 * @buffer: string that is called to line
 * @n: line size
 * @q: buffer size
 */
void bring_inline(char **lineptr, size_t *n, char *buffer, size_t q)
{

	if (*lineptr == NULL)
	{
		if  (q > BUFSIZE)
			*n = q;

		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else if (*n < q)
	{
		if (q > BUFSIZE)
			*n = q;
		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else
	{
		_strcopy(*lineptr, buffer);
		free(buffer);
	}
}
/**
 * get_inline - Read inpt from stream
 * @lineptr: buffer that stores the input
 * @n: lineptr size
 * @stream: stream to read from
 * Return: number of bytes
 */
ssize_t get_inline(char **lineptr, size_t *n, FILE *stream)
{
	int a;
	static ssize_t input;
	ssize_t retval;
	char *buffer;
	char t = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		a = read(STDIN_FILENO, &t, 1);
		if (a == -1 || (a == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (a == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buffer = _reloc(buffer, input, input + 1);
		buffer[input] = t;
		input++;
	}
	buffer[input] = '\0';
	bring_inline(lineptr, n, buffer, input);
	retval = input;
	if (a != 0)
		input = 0;
	return (retval);
}
