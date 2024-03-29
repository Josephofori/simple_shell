#include "simshell.h"

/**
 * _strdup - duplicate string in heap memory.
 * @s: char pointer str
 * Return: duplicated string
 */
char *_strdup(const char *s)
{
	char *new;
	size_t len;

	len = _strlength(s);
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	_memcopy(new, s, len + 1);
	return (new);
}

/**
 * _strlength - Returns length of string.
 * @s: type char pointer
 * Return: Always 0.
 */
int _strlength(const char *s)
{
	int len;

	for (len = 0; s[len] != 0; len++)
	{
	}
	return (len);
}

/**
 * cmp_char - compare chars of strings
 * @str: input.
 * @delimit: delimiter.
 *
 * Return: 1 if are equals, 0 if not.
 */
int cmp_char(char str[], const char *delimit)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; str[i]; i++)
	{
		for (j = 0; delimit[j]; j++)
		{
			if (str[i] == delimit[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}

/**
 * _strtak - splits a string by some delimiter.
 * @str: input.
 * @delimit: delimiter.
 *
 * Return: string splited.
 */
char *_strtak(char str[], const char *delimit)
{
	static char *splitted, *str_end;
	char *str_start;
	unsigned int i, bool;

	if (str != NULL)
	{
		if (cmp_char(str, delimit))
			return (NULL);
		splitted = str;
		i = _strlength(str);
		str_end = &str[i]; /*Store last address*/
	}
	str_start = splitted;
	if (str_start == str_end) /*Reach the end*/
		return (NULL);

	for (bool = 0; *splitted; splitted++)
	{
		/*Breaking loop to find the next token*/
		if (splitted != str_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		/*Replacing delimit for null char*/
		for (i = 0; delimit[i]; i++)
		{
			if (*splitted == delimit[i])
			{
				*splitted = '\0';
				if (splitted == str_start)
					str_start++;
				break;
			}
		}
		if (bool == 0 && *splitted) /*Str != Delim*/
			bool = 1;
	}
	if (bool == 0) /*Str == Delim*/
		return (NULL);
	return (str_start);
}

/**
 * _itsdigit - finds if string passed is a number
 *
 * @s: input
 * Return: 1 if string is a number. 0 in other case.
 */
int _itsdigit(const char *s)
{
	unsigned int i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] < 48 || s[i] > 57)
			return (0);
	}
	return (1);
}
