#include "shell.h"

/**
 * handl_comment - parses the input for comment
 *
 * @input: input argument from stdin
 * Return: string without comment
 */
char *handl_comment(char *input)
{
	int i = 0, j = 0;

	if (*input == '#')
	{
		free(input);
		return (NULL);
	}
	for (i = 1, j = 0; input[i]; i++, j++)
	{
		if (input[i] == '#' && (input[j] == ' ' || input[j] == '\t'))
		{
			input = _realloc(input, i, j + 1);
			input[j] = '\0';
		}
	}

	return (input);
}
