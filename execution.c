#include "shell.h"

/**
 * execution - executes the given command
 *
 * @input: the input string
 * @cmd: global struct variables
 * Return: 1 on success.
 */
int execution(char** input, cmd_t *cmd)
{
	char *dir;
	pid_t pid, ppid;
	int wstatus;
	(void) ppid;

	dir = _which(input[0]);
	printf("dir--[%s]\n", dir);
	if (check_dir_access(input, dir))
		return (1);

	dir = _which(input[0]);
	if ((pid = _fork()) == 0)
		execve(dir, input, cmd->envar);
	else
	{
		do {
				ppid = waitpid(pid, &wstatus, WUNTRACED);
		} while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
	}

	cmd->status = wstatus / 256;
	return (1);
}

/**
 * check_dir_access - checks if the directory is accessible
 *
 * @dir: command directory
 * @input: input string
 * Return: 1 if there is an error, 0 if not
 */
int check_dir_access(char **input, char* dir)
{
	if (dir == NULL)
	{
		free(dir), t_error("invalid command\n");
		return (1);
	}

	if (!_strcmp(input[0], dir))
	{
		if (access(dir, X_OK) == -1)
		{
			t_error("cannot access directory\n");
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(input[0], X_OK) == -1)
		{
			t_error("cannot access command directory\n");
			free(dir);
			return (1);
		}
	}

	return (0);
}
