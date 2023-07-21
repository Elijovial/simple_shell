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

	if (str == 0 || *str = '\0')
		return (-1);

	writtenBytes = write(STDOUT_FILENO, str, _strlen(str));
	if (writtenBytes < 0)
	{
		perror("Err");
	}
	
	if (write(STDOUT_FILENO, &str[i], 1) < 0)
             return (EOF);
     return (i);
}
