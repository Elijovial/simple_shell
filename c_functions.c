#include "shell.h"

/**
 * print_cd_error - prints error messages related to cd command
 * @error_type: type of error to print (e.g "OLDPWD not set", etc.)
 * @shell_name: the name of the shell (e.g., "sh")
 * @command_count: count of commands entered since shell execution
 */
void print_cd_error(const char *error_type, const char *shell_name,
		int command_count)
{
	fprintf(stderr, "%s: %d: cd: %s\n", shell_name, command_count, error_type);
}

/**
 * change_directory_to_home - function to change the cwd to HOME
 * @shell_name: the name of the shell (e.g., "sh")
 * @command_count: the count of commands entered since shell execution
 */
void change_directory_to_home(const char *shell_name, int command_count)
{
	char *home_dir = getenv("HOME");

	if (home_dir == NULL)
	{
		print_cd_error("HOME not set", shell_name, command_count);
		return;
	}

	if (chdir(home_dir) != 0)
		print_cd_error("can't cd to HOME", shell_name, command_count);
}

/**
 * change_directory_to_previous - change cwdir to OLDPWD
 * @shell_name: the name of the shell (e.g., "sh")
 * @command_count: count of commands entered since shell execution
 */
void change_directory_to_previous(const char *shell_name, int command_count)
{
	char *oldpwd = getenv("OLDPWD");

	if (oldpwd == NULL)
	{
		print_cd_error("OLDPWD not set", shell_name, command_count);
		return;
	}

	if (chdir(oldpwd) != 0)
		print_cd_error("can't cd to OLDPWD", shell_name, command_count);
}

/**
 * change_directory_to_specified -change the cwdir to another directory
 * @directory: the path of the directory to change to
 * @shell_name: the name of the shell (e.g., "sh")
 * @command_count: the count of commands entered since shell execution
 */
void change_directory_to_specified(const char *directory,
		const char *shell_name, int command_count)
{
	if (access(directory, F_OK) != 0)
	{
		fprintf(stderr, "%s: %d: cd: %s: No such file or directory\n",
				shell_name, command_count, directory);
		return;
	}

	if (chdir(directory) != 0)
		fprintf(stderr, "%s: %d: cd: can't cd to %s\n",
				shell_name, command_count, directory);
}

/**
 * change_directory - function to change the currentwdir based on args
 * @args: array of arguments for the command
 * @shell_name: the name of the shell (e.g., "sh")
 * @command_count: the count of commands entered since shell execution
 */
void change_directory(char *args[], const char *shell_name, int command_count)
{
	char cwd[1024];

	if (args[1] == NULL)
	{
		change_directory_to_home(shell_name, command_count);
	}
	else if (strcmp(args[1], "-") == 0)
		change_directory_to_previous(shell_name, command_count);
	else
		change_directory_to_specified(args[1], shell_name, command_count);

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		if (setenv("OLDPWD", cwd, 1) != 0)
		{
			fprintf(stderr, "%s: %d: cd: failed to set OLDPWD\n",
			shell_name, command_count);
		}
	}
	else
		fprintf(stderr, "%s: %d: cd: failed to get current directory\n",
		shell_name, command_count);
}
