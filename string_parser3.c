#include "shell.h"

/**
 * get_len - Get the lenght of a number.
 * @n: type int number.
 * Return: Lenght of a number.
 */
int get_len(int n)
{
	unsigned int n1;
	int lenght = 1;

	if (n < 0)
	{
		lenght++;
		n1 = n * -1;
	}
	else
	{
		n1 = n;
	}
	while (n1 > 9)
	{
		lenght++;
		n1 = n1 / 10;
	}

	return (lenght);
}

/**
 * _itoa - function converts int to string.
 * @n: type int number
 * Return: String.
 */
char *_itoa(int n)
{
	unsigned int n1;
	int lenght = get_len(n);
	char *buffer;

	buffer = malloc(sizeof(char) * (lenght + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + lenght) = '\0';

	if (n < 0)
	{
		n1 = n * -1;
		buffer[0] = '-';
	}
	else
	{
		n1 = n;
	}

	lenght--;
	do {
		*(buffer + lenght) = (n1 % 10) + '0';
		n1 = n1 / 10;
		lenght--;
	}
	while (n1 > 0)
		;
	return (buffer);
}

/**
 * copy_info - copies info to create
 * a new env or alias
 * @name: name (env or alias)
 * @value: value (env or alias)
 *
 * Return: new env or alias.
 */
char *copy_info(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = _strlen(name);
	len_value = _strlen(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}
