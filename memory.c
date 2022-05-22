#include "shell.h"

/**
 * free_grid - frees a 2 dimensional grid.
 * @grid: multidimensional array of integers.
 * @height: height of the grid.
 *
 * Return: no return
 */
void free_grid(char **grid, int height)
{
	height -= 1;

	if (grid != NULL && height != 0)
	{
		for (; height >= 0; height--)
		{
			free(grid[height]);
		}
		free(grid);
	}
}

/**
 * free_cmd - frees cmd envar
 *
 * @cmd: cmd struct
 * Return: no return
 */
void free_cmd(cmd_t *cmd)
{
	int i;

	for (i = 0; cmd->envar[i]; i++)
		free(cmd->envar[i]);

	free(cmd->envar);
	free(cmd->pid);
}
