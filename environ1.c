#include "simshell.h"

/**
 * cmp_env - compares env variables names
 * with the name passed.
 * @nenv: name of environment variable
 * @name: name passed
 *
 * Return: 0 if are not equal. Another value if they are.
 */
int cmp_env(const char *nenv, const char *name)
{
	int a;

	for (a = 0; nenv[a] != '='; a++)
	{
		if (nenv[a] != name[a])
		{
			return (0);
		}
	}

	return (a + 1);
}

/**
 * _getenvi - get an environment variable
 * @name: environment variable name
 * @_environ: environment var
 *
 * Return: environment variable value if found.
 * In other case, returns NULL.
 */
char *_getenvi(const char *name, char **_environ)
{
	char *ptr_env;
	int q, mov;

	/* Initialize ptr_env value */
	ptr_env = NULL;
	mov = 0;
	/* Compare all environment variables */
	/* environ is declared in the header file */
	for (q = 0; _environ[q]; q++)
	{
		/* If name and env are equal */
		mov = cmp_env(_environ[q], name);
		if (mov)
		{
			ptr_env = _environ[q];
			break;
		}
	}

	return (ptr_env + mov);
}

/**
 * _env - prints evironment var
 *
 * @datash: relevant data.
 * Return: 1 on success.
 */
int _env(data_shel *datash)
{
	int q, j;

	for (q = 0; datash->_environ[q]; q++)
	{

		for (j = 0; datash->_environ[q][j]; j++)
			;

		write(STDOUT_FILENO, datash->_environ[q], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->stat = 0;

	return (1);
}
