#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LENGTH 1024

int main(void)
{
	char *input = NULL;
	size_t n = 0;
	char *args[MAX_LENGTH / 2 + 1];
	int should_run = 1;
	int result;

	while (should_run)
	{
		if (isatty(STDIN_FILENO) == 1)
		{
			printf("$ ");
		}



		if (getline(&input, &n, stdin) == -1)
		{
			if (isatty(STDIN_FILENO) == 1)
			{
				printf("\n");
			}
			exit(0);
		}

		if (strcmp(input, "exit") == 0) {
			break;
		}

		pid_t pid = fork();
		if (pid < 0)
		{
			fprintf(stderr, "Fork failed\n");
			return 1;
		}
		else if (pid == 0)
		{
			char *token = strtok(input, "\n\t\r ");
			int i = 0;

			while (token != NULL)
			{
				args[i] = token;
				i++;
				token = strtok(NULL, "\n\t\r ");
			}
			args[i] = NULL;

			execvp(args[0], args);
			result = strcmp(input, "$?");
			if (result == 0)                                  {
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
		{
			wait(NULL);
		}
	}

	return (0);
}