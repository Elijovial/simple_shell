#include "shell.h"

/**
 * _print - function to prints strings to stdout
 * @str: string to be printed
 *
 * Return: number of character printed
 */

int _print(const char *str)
{
	size_t writtenBytes;

	if (str == 0 || *str == '\0')
		return (-1);

	writtenBytes = write(STDOUT_FILENO, str, _strlen(str));

	if (writtenBytes < 0 || writtenBytes < (_strlen(str)))
		return (-1);

	return (writtenBytes);
}
