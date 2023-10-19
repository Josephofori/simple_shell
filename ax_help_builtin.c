#include "simshell.h"

/**
 * ax_help - help information.
 * Return: none
 */
void ax_help(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help, _strlength(help));
	help = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, help, _strlength(help));
	help = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, help, _strlength(help));
}
/**
 * ax_help_alias - help information for alias.
 * Return: none
 */
void ax_help_alias(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help, _strlength(help));
	help = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, help, _strlength(help));
}
/**
 * ax_help_cd - help information.
 * Return: none
 */
void ax_help_cd(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, _strlength(help));
	help = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, help, _strlength(help));
}
