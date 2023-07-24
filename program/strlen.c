#include "shell.h"

/**
 * _strlen - function measures the length of a string
 * @str: string to be measured
 * Return: length of a string
 */

size_t _strlen(const char *str)
{
	size_t i;

	for (i = 0; str[i]; i++)
		;

	return (i);
}
