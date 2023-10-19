#include "simshell.h"

/**
 * add_var_node - adds a variable at the end
 * of a r_var list.
 * @head: head of linked list.
 * @lenvar: length of variable.
 * @val: value of variable.
 * @lval: length of value.
 * Return: address of head.
 */
r_var *add_var_node(r_var **head, int lenvar, char *val, int lval)
{
	r_var *new, *temp;

	new = malloc(sizeof(r_var));
	if (new == NULL)
		return (NULL);

	new->len_var = lenvar;
	new->len_val = lval;
	new->val = val;

	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * free_var_list - frees a r_var list
 * @head: head of linked list.
 * Return: none.
 */
void free_var_list(r_var **head)
{
	r_var *cur;
	r_var *temp;

	if (head != NULL)
	{
		cur = *head;
		while ((temp = cur) != NULL)
		{
			cur = cur->next;
			free(temp);
		}
		*head = NULL;
	}
}
