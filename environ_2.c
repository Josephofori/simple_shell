#include "simshell.h"

/**
 * cpy_info - copies info to create
 * new env or alias
 * @name: env or alias name
 * @value: value of env or alias
 *
 * Return: env or alias.
 */
char *cpy_info(char *name, char *value)
{
	int len_name, len_value, len;
	char *new;

	len_name = _strlength(name);
	len_value = _strlength(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	_strcopy(new, name);
	_strcat(new, value);
	_strcat(new, "=");
	_strcat(new, "\0");

	return (new);
}

/**
 * set_env - sets an environment variable
 *
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @datash: data structure (environ)
 * Return: no return
 */
void set_env(char *name, char *value, data_shel *datash)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; datash->_environ[i]; i++)
	{
		var_env = _strdup(datash->_environ[i]);
		name_env = _strtak(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(datash->_environ[i]);
			datash->_environ[i] = cpy_info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	datash->_environ = _relocdp(datash->_environ, i, sizeof(char *) * (i + 2));
	datash->_environ[i] = cpy_info(name, value);
	datash->_environ[i + 1] = NULL;
}

/**
 * _setenvi - compares env variables
 * with the name passed.
 * @datash: data relevant
 *
 * Return: 1 on success.
 */
int _setenvi(data_shel *datash)
{

	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		get_errorr(datash, -1);
		return (1);
	}

	set_env(datash->args[1], datash->args[2], datash);

	return (1);
}

/**
 * _unsetenvi - deletes a environment variable
 *
 * @datash: data relevant (env name)
 *
 * Return: 1 on success.
 */
int _unsetenvi(data_shel *datash)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int a, j, k;

	if (datash->args[1] == NULL)
	{
		get_errorr(datash, -1);
		return (1);
	}
	k = -1;
	for (a = 0; datash->_environ[a]; a++)
	{
		var_env = _strdup(datash->_environ[a]);
		name_env = _strtak(var_env, "=");
		if (_strcmp(name_env, datash->args[1]) == 0)
		{
			k = a;
		}
		free(var_env);
	}
	if (k == -1)
	{
		get_errorr(datash, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (a));
	for (a = j = 0; datash->_environ[a]; a++)
	{
		if (a != k)
		{
			realloc_environ[j] = datash->_environ[a];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(datash->_environ[k]);
	free(datash->_environ);
	datash->_environ = realloc_environ;
	return (1);
}
