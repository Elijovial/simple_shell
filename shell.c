#include "shell.h"

/**
 * main - entry point for shell()
 * Return: 0 if successful
 */

int main(void)
{
	char *input = NULL, *args[MAX_LENGTH];
	size_t n = 0, i = 0;
	pid_t pid;

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
		pid = fork();
		if (pid < 0)
		{
			fprintf(stderr, "Fork failed\n");
			return (1);
		}
		else if (pid == 0)
		{
			char *token = strtok(input, "\n\t\r ");

			while (token != NULL)
			{
				args[i] = token;
				i++;
				token = strtok(NULL, "\n\t\r ");
			}
			args[i] = NULL;
			execvp(args[0], args);
			fprintf(stderr, "Exec failed\n");
			return (1);
		}
		else
			wait(NULL);
	}
	free(input);
	return (0);
}
