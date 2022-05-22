#include "shell.h"

/**
 * swap_char - swaps | and & for non-printed chars
 *
 * @input: input string
 * @bool: type of swap
 * Return: swapped string
 */
char *swap_char(char *input, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; input[i]; i++)
		{
			if (input[i] == '|')
			{
				if (input[i + 1] != '|')
					input[i] = 16;
				else
					i++;
			}

			if (input[i] == '&')
			{
				if (input[i + 1] != '&')
					input[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; input[i]; i++)
		{
			input[i] = (input[i] == 16 ? '|' : input[i]);
			input[i] = (input[i] == 12 ? '&' : input[i]);
		}
	}
	return (input);
}

/**
 * add_nodes - add separators and command lines in the lists
 *
 * @head_s: head of separator list
 * @head_l: head of command lines list
 * @input: input string
 * Return: no return
 */
void add_nodes(sep_t **head_s, line_t **head_l, char *input)
{
	int i;
	char *line;

	input = swap_char(input, 0);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			add_sep_node_end(head_s, input[i]);

		if (input[i] == '|' || input[i] == '&')
		{
			add_sep_node_end(head_s, input[i]);
			i++;
		}
	}

	line = _strtok(input, ";|&");
	do {
		line = swap_char(line, 1);
		add_line_node_end(head_l, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);

}

/**
 * go_next - go to the next command line stored
 *
 * @list_s: separator list
 * @list_l: command line list
 * @cmd: data structure
 * Return: no return
 */
void go_next(sep_t **list_s, line_t **list_l, cmd_t *cmd)
{
	int loop_sep;
	sep_t *ls_s;
	line_t *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (cmd->status == 0)
		{
			if (ls_s->sep == '&' || ls_s->sep == ';')
				loop_sep = 0;
			if (ls_s->sep == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->sep == '|' || ls_s->sep == ';')
				loop_sep = 0;
			if (ls_s->sep == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}


/**
 * apply_seperators - splits command lines according to
 * the separators ;, | and &, and executes them
 *
 * @cmd: data structure
 * @input: input string
 * Return: 0 to exit, 1 to continue
 */
int apply_seperators(cmd_t *cmd, char *input)
{

	sep_t *head_s = NULL, *list_s = NULL;
	line_t *head_l = NULL, *list_l = NULL;
	int ready;

	add_nodes(&head_s, &head_l, input);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		cmd->input = list_l->line;
		cmd->args = get_toks(cmd->input, DELIM);
		ready = execution(cmd);
		free(cmd->args);

		if (ready == 0)
		{
			cmd->ready = 0;
			break;
		}

		go_next(&list_s, &list_l, cmd);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_sep_list(&head_s);
	free_line_list(&head_l);

	if (ready == 0)
		return (0);
	return (1);
}
