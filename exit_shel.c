#include "simshell.h"

/**
 * exit_shel - exits the shell
 *
 * @datash: data relevant
 * Return: 0 on success.
 */
int exit_shel(data_shel *datash)
{
	unsigned int ustatus;
	int is_digit;
	int str_len;
	int big_number;

	if (datash->args[1] != NULL)
	{
		ustatus = _atoi(datash->args[1]);
		is_digit = _itsdigit(datash->args[1]);
		str_len = _strlength(datash->args[1]);
		big_number = ustatus > (unsigned int)INT_MAX;
		if (!is_digit || str_len > 10 || big_number)
		{
			get_errorr(datash, 2);
			datash->stat = 2;
			return (1);
		}
		datash->stat = (ustatus % 256);
	}
	return (0);
}
