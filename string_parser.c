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
	int i = 0;
	char *token = NULL;
	char **output = malloc(MAXARGS * sizeof(char *));

	if (output == NULL)
	{
		free(output);
		exit(EXIT_FAILURE);
	}

	token = _strtok(args, delimiter);
	while (token != NULL)
	{
		output[i] = token;
		i++;
		if (i == MAXARGS)
		{
			output = _realloc(output, i, i * sizeof(char *));
			if (output == NULL)
			{
				free(output);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, delimiter);
	}
	output[i] = NULL;

	return (output);
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

