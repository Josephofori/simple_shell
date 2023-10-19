#include "simshell.h"

/**
 * strcat_cdd - concatenates the message for cd error
 *
 * @datash: data relevant
 * @msg: message to print
 * @error: output message
 * @ver_str: counter line
 * Return: error msg
 */
char *strcat_cdd(data_shel *datash, char *msg, char *error, char *ver_str)
{
	char *illegal_flag;

	_strcopy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, msg);
	if (datash->args[1][0] == '-')
	{
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = datash->args[1][1];
		illegal_flag[2] = '\0';
		_strcat(error, illegal_flag);
		free(illegal_flag);
	}
	else
	{
		_strcat(error, datash->args[1]);
	}

	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}

/**
 * error_get_cdd - error message for cd command
 * @datash: elevant data
 * Return: Error msg
 */
char *error_get_cdd(data_shel *datash)
{
	int length, len_id;
	char *error, *msg, *ver_str;

	ver_str = ax_itoa(datash->count);
	if (datash->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _strlength(datash->args[1]);
	}

	length = _strlength(datash->av[0]) + _strlength(datash->args[0]);
	length += _strlength(ver_str) + _strlength(msg) + len_id + 5;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}

	error = strcat_cdd(datash, msg, error, ver_str);

	free(ver_str);

	return (error);
}

/**
 * errorr_not_found - generic error for command not found
 * @datash: relevant data
 * Return: Error message
 */
char *errorr_not_found(data_shel *datash)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = ax_itoa(datash->count);
	length = _strlength(datash->av[0]) + _strlength(ver_str);
	length += _strlength(datash->args[0]) + 16;
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
	_strcat(error, ": not found\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}

/**
 * error_exit_shel - generic error message for exit in get_exit
 * @datash: relevant data
 *
 * Return: Error msg
 */
char *error_exit_shel(data_shel *datash)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = ax_itoa(datash->count);
	length = _strlength(datash->av[0]) + _strlength(ver_str);
	length += _strlength(datash->args[0]) + _strlength(datash->args[1]) + 23;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}
	_strcopy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, ": Illegal number: ");
	_strcat(error, datash->args[1]);
	_strcat(error, "\n\0");
	free(ver_str);

	return (error);
}
