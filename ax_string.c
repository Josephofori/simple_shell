#include "simshell.h"

/**
 * _strcat - concatenate two strings together
 * @destin: char pointer the destin of the copied str
 * @src: const char pointer the source of str
 * Return: the destin
 */
char *_strcat(char *destin, const char *src)
{
	int a;
	int j;

	for (a = 0; destin[a] != '\0'; a++)
		;

	for (j = 0; src[j] != '\0'; j++)
	{
		destin[a] = src[j];
		a++;
	}

	destin[a] = '\0';
	return (destin);
}
/**
 * *_strcopy - Copies the string pointed to by src.
 * @destin: Type char pointer the destin of copied str
 * @src: Type char pointer the source of str
 * Return: the destin.
 */
char *_strcopy(char *destin, char *src)
{

	size_t a;

	for (a = 0; src[a] != '\0'; a++)
	{
		destin[a] = src[a];
	}
	destin[a] = '\0';

	return (destin);
}
/**
 * _strcmp - Compares two strings.
 * @str1: type str compared
 * @str2: type str compared
 * Return: Always 0.
 */
int _strcmp(char *str1, char *str2)
{
	int i;

	for (i = 0; str1[i] == str2[i] && str1[i]; i++)
		;

	if (str1[i] > str2[i])
		return (1);
	if (str1[i] < str2[i])
		return (-1);
	return (0);
}
/**
 * _strchar - locates a character
 * @s: string
 * @c: character
 * Return: pointer to first occurrence of the character c.
 */
char *_strchar(char *s, char c)
{
	unsigned int a = 0;

	for (; *(s + a) != '\0'; a++)
		if (*(s + a) == c)
			return (s + a);
	if (*(s + a) == c)
		return (s + a);
	return ('\0');
}
/**
 * _strsub - gets length of prefix substring.
 * @s: initial segment.
 * @accept: accepted bytes.
 * Return: number of accepted bytes.
 */
int _strsub(char *s, char *accept)
{
	int a, j, bool;

	for (a = 0; *(s + a) != '\0'; a++)
	{
		bool = 1;
		for (j = 0; *(accept + j) != '\0'; j++)
		{
			if (*(s + a) == *(accept + j))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (a);
}
