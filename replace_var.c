#include "simshell.h"

/**
 * check_environ - checks if variable is env variable
 *
 * @h: linked list head
 * @in: input
 * @data: data structure
 * Return: none
 */
void check_environ(r_var **h, char *in, data_shel *data)
{
	int row1, chr, j, lval;
	char **_envr;

	_envr = data->_environ;
	for (row1 = 0; _envr[row1]; row1++)
	{
		for (j = 1, chr = 0; _envr[row1][chr]; chr++)
		{
			if (_envr[row1][chr] == '=')
			{
				lval = _strlength(_envr[row1] + chr + 1);
				add_var_node(h, j, _envr[row1] + chr + 1, lval);
				return;
			}

			if (in[j] == _envr[row1][chr])
				j++;
			else
				break;
		}
	}

	for (j = 0; in[j]; j++)
	{
		if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
			break;
	}

	add_var_node(h, j, NULL, 0);
}

/**
 * check_var - check if typed variable is $$ or $?
 *
 * @h: linked list head
 * @in: input
 * @st: last status of Shell
 * @data: data structure
 * Return: none
 */
int check_var(r_var **h, char *in, char *st, data_shel *data)
{
	int i, lst, lpd;

	lst = _strlength(st);
	lpd = _strlength(data->pid);

	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				add_var_node(h, 2, st, lst), i++;
			else if (in[i + 1] == '\n')
				add_var_node(h, 0, NULL, 0);
			else if (in[i + 1] == '$')
				add_var_node(h, 2, data->pid, lpd), i++;
			else if (in[i + 1] == '\0')
				add_var_node(h, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				add_var_node(h, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				add_var_node(h, 0, NULL, 0);
			else if (in[i + 1] == ';')
				add_var_node(h, 0, NULL, 0);
			else
				check_environ(h, in + i, data);
		}
	}

	return (i);
}

/**
 * replace_input - replaces string to variables
 *
 * @head: linked list head
 * @input: input
 * @new_input: new input str (replaced)
 * @nlength: new length
 * Return: replaced string
 */
char *replace_input(r_var **head, char *input, char *new_input, int nlength)
{
	r_var *indx;
	int i, j, k;

	indx = *head;
	for (j = i = 0; i < nlength; i++)
	{
		if (input[j] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				new_input[i] = input[j];
				j++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (k = 0; k < indx->len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < indx->len_val; k++)
				{
					new_input[i] = indx->val[k];
					i++;
				}
				j += (indx->len_var);
				i--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[i] = input[j];
			j++;
		}
	}

	return (new_input);
}

/**
 * repl_var -  replace string into vars
 *
 * @input: input
 * @datash: data structure
 * Return: replaced string
 */
char *repl_var(char *input, data_shel *datash)
{
	r_var *head, *indx;
	char *status, *new_input;
	int olen, nlength;

	status = ax_itoa(datash->stat);
	head = NULL;

	olen = check_var(&head, input, status, datash);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	indx = head;
	nlength = 0;

	while (indx != NULL)
	{
		nlength += (indx->len_val - indx->len_var);
		indx = indx->next;
	}

	nlength += olen;

	new_input = malloc(sizeof(char) * (nlength + 1));
	new_input[nlength] = '\0';

	new_input = replace_input(&head, input, new_input, nlength);

	free(input);
	free(status);
	free_var_list(&head);

	return (new_input);
}
