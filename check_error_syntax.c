#include "simshell.h"

/**
 * repeat_char - counts repetitions of a char
 *
 * @input: input
 * @a: index
 * Return: repetitions
 */
int repeat_char(char *input, int a)
{
	if (*(input - 1) == *input)
		return (repeat_char(input - 1, a + 1));

	return (a);
}

/**
 * error_op - finds syntax errors
 *
 * @input: input
 * @a: index
 * @last: last character read
 * Return: index of error. 0 when there are no
 * errors
 */
int error_op(char *input, int a, char last)
{
	int count;

	count = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (error_op(input + 1, a + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (a);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (a);

		if (last == '|')
		{
			count = repeat_char(input, 0);
			if (count == 0 || count > 1)
				return (a);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (a);

		if (last == '&')
		{
			count = repeat_char(input, 0);
			if (count == 0 || count > 1)
				return (a);
		}
	}

	return (error_op(input + 1, a + 1, *input));
}

/**
 * first_character - find first char index
 *
 * @input: input
 * @i: index
 * Return: 1 if there is error. 0 in other case.
 */
int first_character(char *input, int *i)
{

	for (*i = 0; input[*i]; *i += 1)
	{
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;

		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * print_error_syntax - prints if syntax error is found
 *
 * @datash: data structure
 * @input: input
 * @i: error index
 * @bool: msg error control
 * Return: none
 */
void print_error_syntax(data_shel *datash, char *input, int i, int bool)
{
	char *msg1, *msg2, *msg3, *error, *counter;
	int length;

	if (input[i] == ';')
	{
		if (bool == 0)
			msg1 = (input[i + 1] == ';' ? ";;" : ";");
		else
			msg1 = (input[i - 1] == ';' ? ";;" : ";");
	}

	if (input[i] == '|')
		msg1 = (input[i + 1] == '|' ? "||" : "|");

	if (input[i] == '&')
		msg1 = (input[i + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = ax_itoa(datash->count);
	length = _strlength(datash->av[0]) + _strlength(counter);
	length += _strlength(msg1) + _strlength(msg2) + _strlength(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_strcopy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, msg2);
	_strcat(error, msg1);
	_strcat(error, msg3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}

/**
 * check_error_syntax - intermediate function to
 * find and print a syntax error
 *
 * @datash: data structure
 * @input: input
 * Return: 1 when there is error. 0 in other case
 */
int check_error_syntax(data_shel *datash, char *input)
{
	int begin = 0;
	int f_char = 0;
	int i = 0;

	f_char = first_character(input, &begin);
	if (f_char == -1)
	{
		print_error_syntax(datash, input, begin, 0);
		return (1);
	}

	i = error_op(input + begin, 0, *(input + begin));
	if (i != 0)
	{
		print_error_syntax(datash, input, begin + i, 1);
		return (1);
	}

	return (0);
}
