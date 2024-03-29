#include "shell.h"

/**
 * get_shell_name - function to get the name of the shell
 * Return: the name of the shell
 */

char *get_shell_name()
{
	char *shell_name;

	shell_name = getenv("_");
	return (shell_name);
}

/**
 * chK - checks if first arg is an environ
 * @args: 2D array containing tokenized arguments
 * @shell_name: name of shell executed
 * @command_count: count of commands entered
 * @status: variable storing last command exit status
 * @input: stores the command inputted by users
 * Return: exit status for present command
 */

int chK(char *args[], const char *shell_name, int command_count,
		int status, char *input)
{

	if (strcmp(args[0], "exit") == 0)
		status = exiT(args, shell_name, command_count, status, input);
	else if (strcmp(args[0], "env") == 0)
		status = handle_env(shell_name, command_count);

	else if (strcmp(args[0], "cd") == 0)
		handle_cd(args, shell_name, command_count);

	else
		status = search_n_exec_cmd(args, shell_name, command_count);

	return (status);
}

/**
 * handle_cd - function to handle built-in "cd" command
 * @args: array of arguments for the command
 * @shell_name: the name of the shell (e.g., "sh")
 * @command_count: the count of commands entered since shell execution
 */
void handle_cd(char *args[], const char *shell_name, int command_count)
{
	change_directory(args, shell_name, command_count);
}

