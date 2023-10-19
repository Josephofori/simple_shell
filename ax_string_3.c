#include "simshell.h"

/**
 * rev_str - reverses a string.
 * @s: input.
 * Return: none.
 */
void rev_str(char *s)
{
	int counter = 0, a, j;
	char *str, temp;

	while (counter >= 0)
	{
		if (s[counter] == '\0')
			break;
		counter++;
	}
	str = s;

	for (a = 0; a < (counter - 1); a++)
	{
		for (j = a + 1; j > 0; j--)
		{
			temp = *(str + j);
			*(str + j) = *(str + (j - 1));
			*(str + (j - 1)) = temp;
		}
	}
}
