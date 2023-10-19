#include "simshell.h"

/**
 * get_helpp - retrieves help messages according builtin
 * @datash: data structure
 * Return: Return 0
*/
int get_helpp(data_shel *datash)
{

	if (datash->args[1] == 0)
		ax_help_general();
	else if (_strcmp(datash->args[1], "setenv") == 0)
		ax_help_setenv();
	else if (_strcmp(datash->args[1], "env") == 0)
		ax_help_env();
	else if (_strcmp(datash->args[1], "unsetenv") == 0)
		ax_help_unsetenv();
	else if (_strcmp(datash->args[1], "help") == 0)
		ax_help();
	else if (_strcmp(datash->args[1], "exit") == 0)
		ax_help_exit();
	else if (_strcmp(datash->args[1], "cd") == 0)
		ax_help_cd();
	else if (_strcmp(datash->args[1], "alias") == 0)
		ax_help_alias();
	else
		write(STDERR_FILENO, datash->args[0],
		      _strlength(datash->args[0]));

	datash->stat = 0;
	return (1);
}
