#include "shell.h"

/**
 * _setenv - create or modify existing environmental variable in linked list
 * @env: linked list
 * @name: user's typed in command (e.g. "setenv USER Superman")
 * @dir: directory of the command to execute
 * Return: 0 on success, 1 on fail
 */
int _setenv(char *name, char *dir, list_t *env)
{
	int index = 0, j = 0;
	char *cat;

	if (str[1] == NULL || str[2] == NULL)
	{
		write(STDOUT_FILENO, "Too few arguments\n", 18);
		free_double_ptr(str);
		return (-1);
	}
	cat = _strdup(name); /* concatenate strings to be new node data */
	cat = _strcat(cat, "=");
	cat = _strcat(cat, dir);
	index = find_env(*env, name); /* find idx to traverse to node */
	if (index == -1)
	{
		add_end_node(env, cat); /* doesn't exist? create env var */
	}
	else
	{
		holder = *env;
		while (j < index)
		{
			holder = holder->next;
			j++;
		}
		free(holder->var); /* else free malloced data */
		holder->var = _strdup(cat); /* assign to new malloced data */
	}
	free(cat);
	free_double_ptr(str);
	return (0);
}

/**
 * find_env - find given environmental variable in linked list
 * @env: environmental variable linked list
 * @str: variable name
 * Return: idx of node in linked list
 */
int find_env(list_t *env, char *str)
{
	int j = 0, index = 0;

	while (env != NULL)
	{
		j = 0;
		while ((env->var)[j] == str[j]) /* find desired env variable */
			j++;
		if (str[j] == '\0') /* if matches entirely, break, return idx */
			break;
		env = env->next;
		index++;
	}
	if (env == NULL)
		return (-1);
	return (index);
}

/**
 * add_end_node - add node to end of linked list
 * @head: pointer to head of linked list
 * @str: data to new node
 * Return: pointer to new linked list
 */
list_t *add_end_node(list_t **head, char *str)
{
	list_t *new;
	list_t *holder;

	if (head == NULL || str == NULL)
		return (NULL); /* check if address of head is null */
	new = malloc(sizeof(list_t));
	if (new == NULL)
		return (NULL);

	new->var = _strdup(str);
	new->next = NULL;

	holder = *head;
	if (holder != NULL)
	{
		while (holder->next != NULL)
		{
			holder = holder->next;
		}
		holder->next = new;
	}
	else
	{
		*head = new;
	}
	return (*head);
}
