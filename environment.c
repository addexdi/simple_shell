#include "shell.h"

/**
 * _env - prints the evironment variables
 *
 * @cmd: global struct variable.
 * Return: EXIT_SUCCESS on success.
 */
int _env(cmd_t *cmd)
{
	int i, j;

	for (i = 0; cmd->envar[i]; i++)
	{

		for (j = 0; cmd->envar[i][j]; j++)
			;

		write(STDOUT_FILENO, cmd->envar[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	cmd->status = 0;

	return (1);
}


/**
 * cmp_env_name - compares env variables names
 * with the name passed.
 * @nenv: name of the environment variable
 * @name: name passed
 *
 * Return: 0 if are not equal. Another value if they are.
 */
int cmp_env_name(const char *nenv, const char *name)
{
	int i;

	for (i = 0; nenv[i] != '='; i++)
	{
		if (nenv[i] != name[i])
		{
			return (0);
		}
	}

	return (i + 1);
}

/**
 * _getenv - get an environment variable
 * @name: name of the environment variable
 * @_environ: environment variable
 *
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */
char *_getenv(const char *name, char **_environ)
{
	char *ptr_env;
	int i, mov;

	/* Initialize ptr_env value */
	ptr_env = NULL;
	mov = 0;
	/* Compare all environment variables */
	/* environ is declared in the header file */
	for (i = 0; _environ[i]; i++)
	{
		/* If name and env are equal */
		mov = cmp_env_name(_environ[i], name);
		if (mov)
		{
			ptr_env = _environ[i];
			break;
		}
	}

	return (ptr_env + mov);
}

/**
 * _which - Append command to corresponding PATH directory
 *
 * @cmd: input data from getline.
 * @_environ: env data
 * Return: the path of the command or NULL if invalid
 */
char *_which(char *cmd, char **_environ)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	path = _getenv("PATH", _environ);
	if (path)
	{
		ptr_path = _strdup(path);
		len_cmd = _strlen(cmd);
		token_path = _strtok(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (is_cdir(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = _strlen(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			_strcpy(dir, token_path);
			_strcat(dir, "/");
			_strcat(dir, cmd);
			_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = _strtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}
