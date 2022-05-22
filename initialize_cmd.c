#include "shell.h"

/**
 * init_cmd - initialize shell vars
 * @cmd: struct contain shell global vars
 * @av: argv
 *
 * Return: no return
 */
void init_cmd(cmd_t *cmd, char **av)
{
	int i = 0;

	cmd->input = NULL;
	cmd->mode = EXEC;
	cmd->args = NULL;
	cmd->ready = 1;
	cmd->status = 0;
	cmd->av = av;
	cmd->counter = 1;
	cmd->pid = _itoa(getpid());

	for (i = 0; environ[i]; i++)
		;

	cmd->envar = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
		cmd->envar[i] = _strdup(environ[i]);

	cmd->envar[i] = NULL;
}
