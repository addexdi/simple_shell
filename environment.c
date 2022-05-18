#include "shell.h"

/**
 * _env - prints the evironment variables
 *
 * @input: input data from getline.
 * Return: EXIT_SUCCESS on success.
 */
int _env(char **input)
{
	int i, j;

	(void)input;

	for (i = 0; environ[i]; i++)
	{
		for (j = 0; environ[i][j]; j++)
			;

		write(STDOUT_FILENO, environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	return (1);
}

/**
 * _getenv - gets an environment variable
 *
 * @name: name of environmental variable
 *
 * Return: pointer to the value in the environment,
 * or NULL if there is no match *
 */
char *_getenv(const char *name)
{
	int i, j, start;
	char *envar = NULL;

	for (i = 0; environ[i]; i++)
	{
		for (j = 0; environ[i][j] != '='; j++)
		{
			if (environ[i][j] != name[j])
			{
				start = 0;
				break;
			}
			envar = environ[i];
		}
		if (environ[i][j] == '=')
		{
			start = (j + 1);
			break;
		}
	}
	return (envar + start);
}

/**
 * _which - Append command to corresponding PATH directory
 * @input: input data from getline.
 *
 * Return: the path of the command or NULL if invalid
 */
char *_which(char *input)
{
	char *path, *cpy_path, *path_toks, *dir;
	int len_dir, len_input, i;
	struct stat st;

	path = _getenv("PATH");

	if (path)
	{
		cpy_path = _strdup(path);
		len_input = _strlen(input);
		path_toks = _strtok(cpy_path, ":");
		i = 0;
		while (path_toks != NULL)
		{
			if (is_cdir(path, &i))
				if (stat(input, &st) == 0)
					return (input);
			len_dir = _strlen(path_toks);
			dir = malloc(len_dir + len_input + 2);
			if (dir == NULL)
			{
				free(dir), free(cpy_path);
				return (NULL);
			}
			_strcpy(dir, path_toks), _strcat(dir, "/");
			_strcat(dir, input), _strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(cpy_path);
				return (dir);
			}
			free(dir), path_toks = _strtok(NULL, ":");
		}
		free(cpy_path);
		if (stat(input, &st) == 0)
		{
			free(cpy_path);
			return (input);
		}
		return (NULL);
	}
	if (input[0] == '/')
		if (stat(input, &st) == 0)
			return (input);
	return (NULL);
}
