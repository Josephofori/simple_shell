#include "simshell.h"

/**
 * is_cd - checks ":" if its in current directory.
 * @path: type pointer char.
 * @i: int pointer of index.
 * Return: 1 if the path is searchable in the cd, 0 otherwise.
 */
int is_cd(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
		*i += 1;

	return (0);
}

/**
 * _whichcmd - locates a command
 *
 * @cmd: command name
 * @_environ: environment variable
 * Return: location of the command.
 */
char *_whichcmd(char *cmd, char **_environ)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	path = _getenvi("PATH", _environ);
	if (path)
	{
		ptr_path = _strdup(path);
		len_cmd = _strlength(cmd);
		token_path = _strtak(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (is_cd(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = _strlength(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			_strcopy(dir, token_path);
			_strcat(dir, "/");
			_strcat(dir, cmd);
			_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = _strtak(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * is_exec - determine whether its an executable
 *
 * @datash: data structure
 * Return: 0 if not an executable, other number if it does
 */
int is_exec(data_shel *datash)
{
	struct stat st;
	int a;
	char *input;

	input = datash->args[0];
	for (a = 0; input[a]; a++)
	{
		if (input[a] == '.')
		{
			if (input[a + 1] == '.')
				return (0);
			if (input[a + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[a] == '/' && a != 0)
		{
			if (input[a + 1] == '.')
				continue;
			a++;
			break;
		}
		else
			break;
	}
	if (a == 0)
		return (0);

	if (stat(input + a, &st) == 0)
	{
		return (a);
	}
	get_errorr(datash, 127);
	return (-1);
}

/**
 * check_cmd_error - verifies if user has permissions
 *
 * @dir: destination directory
 * @datash: data structure
 * Return: 1 if there is error, 0 if not
 */
int check_cmd_error(char *dir, data_shel *datash)
{
	if (dir == NULL)
	{
		get_errorr(datash, 127);
		return (1);
	}

	if (_strcmp(datash->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			get_errorr(datash, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(datash->args[0], X_OK) == -1)
		{
			get_errorr(datash, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * cmd_execute - executes command lines
 *
 * @datash: data relevant
 * Return: 1 on success.
 */
int cmd_execute(data_shel *datash)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int execu;
	char *dir;
	(void) wpd;

	execu = is_exec(datash);
	if (execu == -1)
		return (1);
	if (execu == 0)
	{
		dir = _whichcmd(datash->args[0], datash->_environ);
		if (check_cmd_error(dir, datash) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (execu == 0)
			dir = _whichcmd(datash->args[0], datash->_environ);
		else
			dir = datash->args[0];
		execve(dir + execu, datash->args, datash->_environ);
	}
	else if (pd < 0)
	{
		perror(datash->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	datash->stat = state / 256;
	return (1);
}
