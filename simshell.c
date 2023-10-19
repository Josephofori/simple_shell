#include "simshell.h"

/**
 * frees_data - frees data struct
 *
 * @datash: data structure
 * Return: none
 */
void frees_data(data_shel *datash)
{
	unsigned int i;

	for (i = 0; datash->_environ[i]; i++)
	{
		free(datash->_environ[i]);
	}

	free(datash->_environ);
	free(datash->pid);
}

/**
 * sets_data - initialize data struct
 *
 * @datash: data structure
 * @av: arg vector
 * Return: none
 */
void sets_data(data_shel *datash, char **av)
{
	unsigned int i;

	datash->av = av;
	datash->input = NULL;
	datash->args = NULL;
	datash->stat = 0;
	datash->count = 1;

	for (i = 0; environ[i]; i++)
		;

	datash->_environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		datash->_environ[i] = _strdup(environ[i]);
	}

	datash->_environ[i] = NULL;
	datash->pid = ax_itoa(getpid());
}

/**
 * main - Entry point
 *
 * @ac: argu count
 * @av: argu vector
 *
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
	data_shel datash;
	(void) ac;

	signal(SIGINT, get_signalint);
	sets_data(&datash, av);
	shel_loop(&datash);
	frees_data(&datash);
	if (datash.stat < 0)
		return (255);
	return (datash.stat);
}
