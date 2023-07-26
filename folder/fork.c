#include "shell.h"

/**
 * fork_strtok - function that forks and tokenize
 * @input:  a pointer to character
 * Return: 0 on success
 */

int fork_strtok(char *input)
{
	int i, result;
	char *args[MAX_LENGTH];
	pid_t pid;

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
			result = strcmp(input, "$?");
			if (result == 0)
			{
				fprintf(stderr, "%s: %d: 0: not found\n", getenv("_"), i);
			}
			else if (result == -1 && result == 1)
			{
				fprintf(stderr, "%s: %d: %d: %s: not found\n", getenv("_"), i, WEXITSTATUS(system(args[0])), args[0]);
			}
			else
				fprintf(stderr,  "%s: %d: %s: not found\n", getenv("_"), i, args[0]);
			return (1);
		}
		else
			wait(NULL);
	
}
