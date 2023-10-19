#include "simshell.h"

/**
 * _memcopy - copies information between pointers.
 * @newptr: destination pointer.
 * @ptr: source pointer.
 * @size: size of new pointer.
 *
 * Return: none.
 */
void _memcopy(void *newptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_newptr = (char *)newptr;
	unsigned int a;

	for (a = 0; a < size; a++)
		char_newptr[a] = char_ptr[a];
}

/**
 * _reloc - reallocates memory block.
 * @ptr: pointer to previous memory allocated.
 * @old_size: size of allocated space of ptr.
 * @new_size: new size of new memory block.
 *
 * Return: ptr.
 * if new_size == old_size, return ptr without changes.
 * if malloc fail, returns NULL.
 */
void *_reloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);

	if (new_size < old_size)
		_memcopy(newptr, ptr, new_size);
	else
		_memcopy(newptr, ptr, old_size);

	free(ptr);
	return (newptr);
}

/**
 * _relocdp - reallocates memory block for double pointer.
 * @ptr: previouslly allocated double pointer to the memory.
 * @old_size: size of allocated space of ptr.
 * @new_size: new size of the new memory block.
 *
 * Return: ptr.
 * if new_size == old_size, return ptr without changes.
 * if malloc fail, returns NULL.
 */
char **_relocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **newptr;
	unsigned int a;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(sizeof(char *) * new_size);
	if (newptr == NULL)
		return (NULL);

	for (a = 0; a < old_size; a++)
		newptr[a] = ptr[a];

	free(ptr);

	return (newptr);
}
