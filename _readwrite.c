#include "shell.h"

/**
 * _readwrite - reads the input string.
 *
 * @is_eof: return value of getline function
 * @status: determines if the shell is interactive
 * Return: the input string.
 */
char *_readwrite(int status, int *is_eof)
{
	char *buffer = NULL;
	size_t bufsize = 0;

	prompt(status);
	*is_eof = getline(&buffer, &bufsize, stdin);

	return (buffer);
}
