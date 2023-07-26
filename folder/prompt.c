#include "shell.h"

/**
 * main - entry point for shell()
 * Return: 0 if successful
 */

int main(void)
{
	char *input = NULL, *args[MAX_LENGTH];
	size_t n = 0;

while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
			printf("$ ");
		if (getline(&input, &n, stdin) == -1)
		{
			if (isatty(STDIN_FILENO) == 1)
				printf("\n");
			exit(0);
		}
		if (strcmp(input, "exit") == 0)
			break;
		fork_strtok(input);
	}
	return (0);
}
