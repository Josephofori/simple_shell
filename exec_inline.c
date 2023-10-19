#include "simshell.h"

/**
 * exec_inline - locates builtins and commands
 *
 * @datash: relevant data (args)
 * Return: 1 on success.
 */
int exec_inline(data_shel *datash)
{
	int (*builtin)(data_shel *datash);

	if (datash->args[0] == NULL)
		return (1);

	builtin = get_builtins(datash->args[0]);

	if (builtin != NULL)
		return (builtin(datash));

	return (cmd_execute(datash));
}
