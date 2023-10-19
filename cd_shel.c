#include "simshell.h"

/**
 * cd_shel - change current directory
 *
 * @datash: data relevant
 * Return: 1 on success
 */
int cd_shel(data_shel *datash)
{
	char *dir;
	int ishome, ishome2, isddash;

	dir = datash->args[1];

	if (dir != NULL)
	{
		ishome = _strcmp("$HOME", dir);
		ishome2 = _strcmp("~", dir);
		isddash = _strcmp("--", dir);
	}

	if (dir == NULL || !ishome || !ishome2 || !isddash)
	{
		cd_to_hom(datash);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		cd_prev(datash);
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		cd_dott(datash);
		return (1);
	}

	cd_tto(datash);

	return (1);
}
