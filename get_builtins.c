#include "shell.h"

/**
 * get_builtin - checks for builtins and returns the
 *     associated function
 *
 * @input: the input string
 * Return: the function if found
 */
int (*get_builtin(char *input))(cmd_t *)
{
	int i = 0;

	built_t builtin[] = {
		{ "env", _env },
		{ "exit", exit_sh },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", c_dir },
		{ "help", get_help },
		{ NULL, NULL }
	};

	for (i = 0; builtin[i].name; i++)
	{
		if (!_strcmp(builtin[i].name, input))
			break;
	}
	return (builtin[i].f);
}

/**
 * get_help - function that retrieves help messages according builtin
 * @cmd: data structure (args and input)
 * Return: Return 0
*/
int get_help(cmd_t *cmd)
{

	if (cmd->args[1] == 0)
		aux_help_general();
	else if (_strcmp(cmd->args[1], "setenv") == 0)
		aux_help_setenv();
	else if (_strcmp(cmd->args[1], "env") == 0)
		aux_help_env();
	else if (_strcmp(cmd->args[1], "unsetenv") == 0)
		aux_help_unsetenv();
	else if (_strcmp(cmd->args[1], "help") == 0)
		aux_help();
	else if (_strcmp(cmd->args[1], "exit") == 0)
		aux_help_exit();
	else if (_strcmp(cmd->args[1], "cd") == 0)
		aux_help_cd();
	else if (_strcmp(cmd->args[1], "alias") == 0)
		aux_help_alias();
	else
		write(STDERR_FILENO, cmd->args[0],
			_strlen(cmd->args[0]));

	cmd->status = 0;
	return (1);
}

/**
 * exit_sh - exits the shell
 *
 * @cmd: struct of global variables
 * Return: 0 on success.
 */
int exit_sh(cmd_t *cmd)
{
	unsigned int ustatus = 0;
	int is_digit = 0;
	int str_len = 0;
	int big_number = 0;

	if (cmd->args[1])
	{
		ustatus = _atoi(cmd->args[1]);
		is_digit = _isdigit(cmd->args[1]);
		str_len = _strlen(cmd->args[1]);
		big_number = ustatus > (unsigned int)INT_MAX;
		if (!is_digit || str_len > 10 || big_number)
		{
			t_error("Invalid exit status");
			cmd->status = 2;
		}
		cmd->status = (ustatus % 256);
		cmd->ready = 0;
	}
	cmd->ready = 0;
	return (0);
}
