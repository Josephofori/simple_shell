#include "simshell.h"

/**
 * errorr_env - error message for env
 * @datash: relevant data
 * Return: error msg.
 */
char *errorr_env(data_shel *datash)
{
	int length;
	char *error;
	char *ver_str;
	char *msg;

	ver_str = ax_itoa(datash->count);
	msg = ": Unable to add/remove from environment\n";
	length = _strlength(datash->av[0]) + _strlength(ver_str);
	length += _strlength(datash->args[0]) + _strlength(msg) + 4;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}

	_strcopy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, msg);
	_strcat(error, "\0");
	free(ver_str);

	return (error);
}

/**
 * errorr_path_126 - error message for path and denied permission.
 * @datash: relevant data
 *
 * Return: error string.
 */
char *errorr_path_126(data_shel *datash)
{
	int length;
	char *ver_str;
	char *error;

	ver_str = ax_itoa(datash->count);
	length = _strlength(datash->av[0]) + _strlength(ver_str);
	length += _strlength(datash->args[0]) + 24;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	_strcopy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, ": Permission denied\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}
