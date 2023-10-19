#include "simshell.h"

/**
 * add_sep_node - adds a separator found at the end
 * of sep_list.
 * @head: linked list head.
 * @sep: separator found (& | ;).
 * Return: address of head.
 */
sep_list *add_sep_node(sep_list **head, char sep)
{
	sep_list *new, *temp;

	new = malloc(sizeof(sep_list));
	if (new == NULL)
		return (NULL);

	new->separator = sep;
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
 * free_sep_listt - free a sep_list
 * @head: linked list head.
 * Return: none.
 */
void free_sep_listt(sep_list **head)
{
	sep_list *temp;
	sep_list *cur;

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

/**
 * add_line_node - adds command line at the end
 * of a line_list.
 * @head: head of linked list.
 * @line: command line.
 * Return: address of the head.
 */
line_list *add_line_node(line_list **head, char *line)
{
	line_list *new, *temp;

	new = malloc(sizeof(line_list));
	if (new == NULL)
		return (NULL);

	new->next = NULL;
	new->line = line;
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
 * frees_line_list - frees line_list
 * @head: head of linked list.
 * Return: none.
 */
void frees_line_list(line_list **head)
{
	line_list *cur;
	line_list *temp;

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
