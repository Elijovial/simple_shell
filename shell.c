#include "shell.h"

/**
 * main - entry point for shell()
 *
 * Return: 0 if successful
 */

int main(void)
{
	char *input = NULL, *args[MAX_LENGTH];
<<<<<<< HEAD
	size_t n = 0;
	int result, i = 0;
=======
	size_t input_size = 0, i = 0;
>>>>>>> 33eca896bce497641a43140351fb2f6f1aa6de07
	pid_t pid;

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
			printf("$ ");
		if (getline(&input, &input_size, stdin) == -1)
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
<<<<<<< HEAD
		{
			char *token = strtok(input, "\n\t\r ");
=======
		 {
			char *token = strtok(input, "\n\t\r ");

>>>>>>> 33eca896bce497641a43140351fb2f6f1aa6de07
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
	return (0);
}
