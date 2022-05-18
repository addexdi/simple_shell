#include "shell.h"

/**
 * init_cmd - initialize shell vars
 * @cmd: struct contain shell global vars
 *
 * Return: no return
 */
void init_cmd(cmd_t *cmd)
{
	int i = 0;

	cmd->mode = 0;
	cmd->args = NULL;
	cmd->ready = 1;
	cmd->status = 0;

	for (i = 0; environ[i]; i++)
		;

	cmd->envar = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
		cmd->envar[i] = _strdup(environ[i]);

	cmd->envar[i] = NULL;
}
