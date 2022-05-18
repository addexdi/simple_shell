#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

/**
 * open_console - opens the console
 *
 * Return: nothing
 */
void open_console(void)
{
	int fd;

	while ((fd = open("/dev/console", O_RDWR)) >= 0)
	{
		if (fd >= 3)
		{
			close(fd);
			break;
		}
	}
}

/**
 * prompt - write the shell prompt to stdin
 *
 * @status: determines if the shell is interactive
 * Return: nothing
 */
void prompt(int status)
{
	if (status)
		write(STDIN_FILENO, ":) ", 3);
}

/**
 * t_error - error handler
 *
 * @s: error message
 * Return: nothing
 */
void t_error(char *s)
{
	write(STDERR_FILENO, s, _strlen(s));
}

/**
 * _fork - creates a child process
 *
 * Return: the process ID
 */
int _fork(void)
{
	pid_t id = fork();

	if (id < 0)
	{
		t_error("Fork failed\n");
		return (1);
	}
	return (id);
}

/**
 * handl_sigint - Handle signals
 * @sig: Signal parameter
 * Return: nothing
 */
void handl_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "<saMosC/> SIGINT\n", 18);
}
