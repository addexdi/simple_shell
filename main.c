#include "shell.h"

/**
 * main - Entry point of the shell
 *
 * @ac: Argument count
 * @av: Argument vector
 *
 * Return: the (int)value of status.
 */
int main(int ac __attribute__((unused)), char **av __attribute__((unused)))
{
	char *buf = NULL, *bufkill = buf, *c_input = NULL;
	cmd_t cmd;
	ssize_t state = 0;
	size_t buflen = 0;
	char **input = NULL;

	signal(SIGINT, handl_sigint);
	open_console();
	init_cmd(&cmd);

	while (cmd.ready)
	{
		state = isatty(STDIN_FILENO);
		prompt(state);

		if (getline(&buf, &buflen, stdin) <= EOF)
			cmd.ready = 0, free(bufkill), exit(EXIT_SUCCESS);

		setcmd(buf, &cmd);
		c_input = handl_comment(buf);
		if (c_input == NULL || c_input[0] == '\n')
			continue;

		input = get_toks(c_input, DELIM), free(c_input);

		if (parse_builtins(input, &cmd))
		{
			free(input);
			continue;
		}

		execution(input, &cmd);
		free(input), free(bufkill), free_cmd(&cmd);
	}
	/*free(input), free(buf), free(c_input), free_cmd(&cmd);*/
	return (cmd.status);
}
