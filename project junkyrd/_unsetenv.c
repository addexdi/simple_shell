#include "shell.h"
/**
 * _unsetenv - remove node in environmental linked list
 * @env: linked list
 * @str: user's typed in command (e.g. "unsetenv MAIL")
 * Return: 0 on success
 */
int _unsetenv(list_t **env, char **str)
{
	int index = 0, j = 0;

	if (str[1] == NULL)
	{
		write(STDOUT_FILENO, "Too few arguments\n", 18);
		free_double_ptr(str);
		return (-1);
	}
	index = find_env(*env, str[1]); /* get idx of node to delete */
	free_double_ptr(str);
	if (index == -1) /* check if index errored */
	{
		write(STDOUT_FILENO, "Cannot find\n", 12);
		return (-1);
	}
	j = delete_nodeint_at_index(env, index); /* delete node */
	if (j == -1)
	{
		write(STDOUT_FILENO, "Cannot find\n", 12);
		return (-1);
	}
	return (0);
}
