#include "shell.h"

/**
 * get_toks - get tokens from input
 *
 * @args: input string.
 * @delimiter: delimiter.
 * Return: a vector of the splited input strings.
 */
char **get_toks(char *args, char *delimiter)
{
	size_t bsize;
	size_t i;
	char **tokens;
	char *token;

	bsize = MAXARGS;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(args, delimiter);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += MAXARGS;
			tokens = _reallocdp(tokens, i, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, delimiter);
		tokens[i] = token;
	}

	return (tokens);
}

/**
 * _isdigit - defines if string passed is a number
 *
 * @str: input string
 * Return: 1 if string is a number. 0 in other case.
 */
int _isdigit(const char *str)
{
	unsigned int i = 0;

	for (i = 0; str[i]; i++)
	{
		if (str[i] < 48 || str[i] > 57)
			return (0);
	}
	return (1);
}

/**
 * str_reverse - reverses a string.
 * @s: input string.
 * Return: no return.
 */
void str_reverse(char *s)
{
	int count = 0, i = 0, j = 0;
	char *str, temp;

	while (count >= 0)
	{
		if (s[count] == '\0')
			break;
		count++;
	}
	str = s;

	for (i = 0; i < (count - 1); i++)
	{
		for (j = i + 1; j > 0; j--)
		{
			temp = *(str + j);
			*(str + j) = *(str + (j - 1));
			*(str + (j - 1)) = temp;
		}
	}
}

/**
 * _strcmp - comparing strings
 *
 * @str_a: first string to compare
 * @str_b: second string to compare
 *
 * Return: Always 0.
 */
int _strcmp(char *str_a, char *str_b)
{
	int i = 0;

	for (i = 0; str_a[i] != '\0' && str_b[i] != '\0'; i++)
	{
		if (str_a[i] != str_b[i])
			return (str_a[i] - str_b[i]);
	}
	return (0);
}

/**
 * *_strcat - concatenates two strings
 * @dest: pointer destination
 * @src: pointer source
 * Return: address of dest
 */

char *_strcat(char *dest, char *src)
{
	int a = -1, i = 0;

	for (i = 0; dest[i] != '\0'; i++)
	;

	do {
		a++;
		dest[i] = src[a];
		i++;
	} while (src[a] != '\0');

	return (dest);
}

