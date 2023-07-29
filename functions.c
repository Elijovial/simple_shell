#include "shell.h"

/**
 * check_for_non_digit - checks if string contains non-digits
 * @str: string to check its content for non-digits
 * Return: true if there is a non-digit, else false if all digits
 */

int check_for_non_digit(const char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (1);
		str++;
	}

	return (0);

}

/**
 * tokenize_input - function to tokenize user input
 * @input: user input string
 * @args: array to store the tokenized arguments
 * Return: number of arguments tokenized
 */
int tokenize_input(char *input, char *args[])
{
	int i = 0;
	char *token = strtok(input, " \t\n\r");

	while (token != NULL)
	{
		args[i] = token;
		i++;
		token = strtok(NULL, " \t\n\r");
	}
	args[i] = NULL;

	return (i);
}

