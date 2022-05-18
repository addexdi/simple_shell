#include "shell.h"

/**
 * parse_builtins - checks for builtins and executes them
 *
 * @input: the input string
 * @cmd: the command struct
 * Return: 1 on success and 0 on failure
 */
int parse_builtins(char **input, cmd_t *cmd)
{
	int i = 0;

	built_t builtin[] = {
		{"env", _env},
		{NULL, NULL}
	};

	if (!_strcmp("exit", input[0]))
		return (exit_sh(input, cmd));

	for (i = 0; builtin[i].name; i++)
	{
		if (!_strcmp(builtin[i].name, input[0]))
			return (builtin[i].f(input));
	}
	return (0);
}
