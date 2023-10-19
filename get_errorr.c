#include "simshell.h"

/**
 * get_errorr - calls error according the builtin
 * @datash: data structure
 * @eval: error value
 * Return: error
 */
int get_errorr(data_shel *datash, int eval)
{
	char *error;

	switch (eval)
	{
	case -1:
		error = errorr_env(datash);
		break;
	case 126:
		error = errorr_path_126(datash);
		break;
	case 127:
		error = errorr_not_found(datash);
		break;
	case 2:
		if (_strcmp("exit", datash->args[0]) == 0)
			error = error_exit_shel(datash);
		else if (_strcmp("cd", datash->args[0]) == 0)
			error = error_get_cdd(datash);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlength(error));
		free(error);
	}

	datash->stat = eval;
	return (eval);
}
