#include "shell.h"

/**
 * setcmd - sets the mode of execution
 *
 * @buf: the buffer containing the arguments
 * @cmd: the command struct
 * Return: nothing
 */
void setcmd(char *buf, cmd_t *cmd)
{
	if (!buf[0])
		exit(EXIT_FAILURE);

	cmd->mode = EXEC;
}
