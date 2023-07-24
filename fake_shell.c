#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LENGTH 1024

/**
 * execute_command - function to execute a command
 * @args: array of arguments for the command
 * Return: 0 on success, -1 on failure
 */
int execute_command(char *args[])
{
	int j = 0;
	pid_t pid = fork();

	if (pid < 0)
	{
		fprintf(stderr, "Fork failed\n");
		return (-1);
	}
	else if (pid == 0)
	{

		while(j >= 0)
		{
			j++;
			execvp(args[0], args);
			fprintf(stderr, "%s: %d: %s: not found\n", getenv("_"), j, args[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(NULL);
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

/**
 * handle_cd - function to handle built-in "cd" command
 * @args: array of arguments for the command
 */
void handle_cd(char *args[])
{
	int num_args = tokenize_input(args[1], args);

	if (num_args != 1)
		fprintf(stderr, "Usage: cd <directory>\n");
	else if (chdir(args[1]) != 0)
		perror("cd");
}

/**
 * search_and_execute_command - function to search and execute command in PATH
 * @args: array of arguments for the command
 */
void search_and_execute_command(char *args[])
{
	char path[MAX_LENGTH];
	char *path_token;
	int found = 0;
	char *path_env = getenv("PATH");

	strcpy(path, path_env);

	path_token = strtok(path, ":");
	while (path_token != NULL)
	{
		char full_path[MAX_LENGTH];

		strcpy(full_path, path_token);
		strcat(full_path, "/");
		strcat(full_path, args[0]);
		if (access(full_path, X_OK) == 0)
		{
			found = 1;
			execute_command(args);
			break;
		}
		path_token = strtok(NULL, ":");
	}

	if (!found)
		execute_command(args);
}

/**
 * main - entry point for the shell
 * Return: 0 if successful
 */
int main(void)
{
	char *input = NULL, *args[MAX_LENGTH];
	size_t n = 0;
	int num_args;

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
			printf("$ ");

		if (getline(&input, &n, stdin) == -1)
		{
			if (isatty(STDIN_FILENO) == 1)
				printf("\n");
		
			free(input);
			exit(0);
		}

		input[strcspn(input, "\n")] = '\0';

		if (strcmp(input, "exit") == 0)
			break;
		num_args = tokenize_input(input, args);

		if (num_args == 0)
			continue;
		if (strcmp(args[0], "cd") == 0)
		{
			handle_cd(args);
			continue;

		}
		if (strchr(args[0], '/') == NULL)
			search_and_execute_command(args);
		else
			execute_command(args);
	}

	free(input);
	return (0);
}
