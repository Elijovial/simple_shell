#include "shell.h"

/**
 * _puts - function to prints strings to stdout
 * @str: string to be printed
 *
 * Return: number of character printed
 */

int _puts(const char *str)
{
	size_t writtenBytes;

	if (str == 0 || *str == '\0')
		return (-1);

	writtenBytes = write(STDOUT_FILENO, str, _strlen(str));
	if (writtenBytes < 0)
	{
		perror("Error writing to standard output");
		return (-1);
	}

	if (writtenBytes < len)
	{
		perror("Error writing characters to standard output");
		return (-1);
	}

	if (write(STDOUT_FILENO, "\n", 1) < 0)
	{
		perror("Error writing newline character to standard output");
		return (-1);
	}

	return (writtenBytes + 1);
}
