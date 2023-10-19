#include "simshell.h"

/**
 * get_builtins - builtin that pass the command in arg
 * @cmd: command
 * Return: pointer of the builtin command
 */
int (*get_builtins(char *cmd))(data_shel *)
{
	builtin_t builtin[] = {
		{ "env", _env },
		{ "exit", exit_shel },
		{ "setenv", _setenvi },
		{ "unsetenv", _unsetenvi },
		{ "cd", cd_shel },
		{ "help", get_helpp },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; builtin[i].name; i++)
	{
		if (_strcmp(builtin[i].name, cmd) == 0)
			break;
	}

	return (builtin[i].f);
}
