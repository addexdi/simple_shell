#include "shell.h"

/**
 * cd_home - changes to home directory
 *
 * @cmd: global struct variable
 * Return: EXIT_SUCCESS
 */
int cd_home(cmd_t *cmd)
{
	char *p_cwd, *home;
	char cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	p_cwd = _strdup(cwd);

	home = _getenv("HOME", cmd->envar);

	if (home == NULL)
	{
		set_env("OLDPWD", p_cwd, cmd);
		free(p_cwd);
		return (1);
	}

	if (chdir(home) == -1)
	{
		free(p_cwd);
		t_error("Cannot go home\n");
		return (1);
	}

	write(STDOUT_FILENO, home, _strlen(home));
	write(STDOUT_FILENO, "\n", 1);

	set_env("OLDPWD", p_cwd, cmd);
	set_env("PWD", home, cmd);
	free(p_cwd);
	return (1);
}

/**
 * cd_back - changes to the previous directory
 *
 * @cmd: global struct variable
 * Return: EXIT_SUCCESS
 */
int cd_back(cmd_t *cmd)
{
	char cwd[PATH_MAX];
	char *p_cwd, *p_oldcwd, *cp_cwd, *cp_oldcwd;

	getcwd(cwd, sizeof(cwd));
	cp_cwd = _strdup(cwd);

	p_oldcwd = _getenv("OLDPWD", cmd->envar);

	if (p_oldcwd == NULL)
		cp_oldcwd = cp_cwd;
	else
		cp_oldcwd = _strdup(p_oldcwd);

	set_env("OLDPWD", cp_cwd, cmd);

	if (chdir(cp_oldcwd) == -1)
		set_env("PWD", cp_cwd, cmd);
	else
		set_env("PWD", cp_oldcwd, cmd);

	p_cwd = _getenv("PWD", cmd->envar);

	write(STDOUT_FILENO, p_cwd, _strlen(p_cwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_cwd);
	if (p_oldcwd)
		free(cp_oldcwd);

	chdir(p_cwd);
	return (1);
}

/**
 * cd_curr - changes to the current directory
 *
 * @cmd: global struct variable
 * Return: EXIT_SUCCESS
 */
int cd_curr(cmd_t *cmd)
{
	char cwd[PATH_MAX];
	char *cp_cwd;

	getcwd(cwd, sizeof(cwd));
	cp_cwd = _strdup(cwd);

	set_env("PWD", cp_cwd, cmd);

	write(STDOUT_FILENO, cp_cwd, _strlen(cp_cwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_cwd);
	return (1);
}

/**
 * cd_parent - changes to the current directory
 *
 * @cmd: global struct variable
 * Return: EXIT_SUCCESS
 */
int cd_parent(cmd_t *cmd)
{
	char cwd[PATH_MAX];
	char *cp_cwd, *cp_strtok_cwd;

	getcwd(cwd, sizeof(cwd));
	cp_cwd = _strdup(cwd);
	set_env("OLDPWD", cp_cwd, cmd);

	if (!_strcmp("/", cp_cwd))
	{
		free(cp_cwd);
		return (1);
	}

	cp_strtok_cwd = cp_cwd;
	str_reverse(cp_strtok_cwd);

	cp_strtok_cwd = _strtok(cp_strtok_cwd, "/");
	if (cp_strtok_cwd != NULL)
	{
		cp_strtok_cwd = _strtok(NULL, "\0");
		if (cp_strtok_cwd != NULL)
			str_reverse(cp_strtok_cwd);
	}

	if (cp_strtok_cwd != NULL)
	{
		chdir(cp_strtok_cwd);
		set_env("PWD", cp_strtok_cwd, cmd);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", cmd);
	}

	write(STDOUT_FILENO, cp_strtok_cwd, _strlen(cp_strtok_cwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_cwd);
	return (1);
}

/**
 * cd_path - changes to a directory given
 * by the user
 *
 * @cmd: global struct variable
 * @dir: directory to change to
 * Return: no return
 */
int cd_path(char *dir, cmd_t *cmd)
{
	char cwd[PATH_MAX];
	char *cp_cwd, *cp_dir;

	getcwd(cwd, sizeof(cwd));

	if (chdir(dir) == -1)
	{
		t_error("Cannot change to the given directory\n");
		return (1);
	}
	cp_cwd = _strdup(cwd);
	set_env("OLDPWD", cp_cwd, cmd);

	cp_dir = _strdup(dir);
	set_env("PWD", cp_dir, cmd);

	write(STDOUT_FILENO, cp_dir, _strlen(cp_dir));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_cwd);
	free(cp_dir);

	chdir(dir);
	return (1);
}
