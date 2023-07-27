#include "shell.h"

/**
 * execute_command - function to execute a command
 * @args: array of arguments for the command
 * @shell_name: the name of the shell (e.g., "sh")
 * @command_count: the count of commands entered since shell execution
 * Return: 0 on success, -1 on failure
 */
int execute_command(char *args[], const char *shell_name, int command_count)
{
	pid_t pid;
	int status;

	if (access(args[0], F_OK) != 0)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
				shell_name, command_count, args[0]);
		return (127);
	}
	pid = fork();
	if (pid < 0)
	{
		fprintf(stderr, "Fork failed\n");
		return (-1);
	}
	else if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			fprintf(stderr, "%s: %d: %s: not found\n",
					shell_name, command_count, args[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			return (WEXITSTATUS(status));
		}
	}

	return (status);
}


/**
 * search_n_exec_cmd - function to search and execute command in PATH
 * @args: array of arguments for the command
 * @shell_name: the name of the shell (e.g., "sh")
 * @command_count: the count of commands entered since shell execution
 * Return: status value
 */
int search_n_exec_cmd(char *args[], const char *shell_name, int command_count)
{
	char path[MAX_LENGTH], full_path[MAX_LENGTH];
	char *path_token, *path_env;
	int found = 0;

	path_env = getenv("PATH");
	strcpy(path, path_env);
	path_token = strtok(path, ":");

	while (path_token != NULL)
	{
		strcpy(full_path, path_token);
		strcat(full_path, "/");
		strcat(full_path, args[0]);
		if (access(full_path, X_OK) == 0)
		{
			args[0] = full_path;
			found = 1;
			execute_command(args, shell_name, command_count);
			break;
		}
		path_token = strtok(NULL, ":");
	}

	if (!found)
		return (execute_command(args, shell_name, command_count));
	return (127);
}

/**
 * main - entry point of the shell program
 * Return: 0 if successful
 */

int main(void)
{
	char *input = NULL, *args[MAX_LENGTH] = {0};
	size_t n = 0;
	int command_count = 0, num_args, status = 0;
	char *shell_name = get_shell_name();

	while (1)
	{
		command_count++;
		if (isatty(STDIN_FILENO) == 1)
			printf("$ ");

		if (getline(&input, &n, stdin) == -1)
		{
			if (isatty(STDIN_FILENO) == 1)
				printf("\n");
			free(input);
			exit(status);
		}

		input[strcspn(input, "\n")] = '\0';

		if (strcmp(input, "exit") == 0)
			break;
		num_args = tokenize_input(input, args);
		if (num_args == 0)
			continue;
		if (strcmp(args[0], "cd") == 0)
		{
			handle_cd(args, shell_name, command_count);
			continue;
		}

		if (strchr(args[0], '/') == NULL)
			status = search_n_exec_cmd(args, shell_name, command_count);
		else
			status = execute_command(args, shell_name, command_count);
	}
	free(input);
	return (status);
}
