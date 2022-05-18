#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/wait.h>
#include <signal.h>

#define EXEC 1
#define MAXARGS 10
#define DELIM " \t\n\r\a"

extern char **environ;

/**
 * struct cmd_t - shell env vars
 * @mode: determines the mode of execution
 * @args: the arguments to be executed
 * @ready: determines if the shell should run.
 * @status: the status of the last command executed.
 *
 * Description: Struct contain all shell vars.
 */
typedef struct cmd_t
{
	int mode;
	char **args;
	int ready;
	int status;
	char **envar;
} cmd_t;

void open_console(void);
void init_cmd(cmd_t *cmd);
void prompt(int status);
void t_error(char *s);
int _fork(void);
void setcmd(char *buf, cmd_t *cmd);
void *_realloc(void *ptr, size_t old_size, size_t new_size);
void runcmd(char *dir, char **input, cmd_t *cmd);
ssize_t _getline(char **line_ptr, size_t *n, FILE *stream);
char *_strtok(char *strn, const char *delim);
void handl_sigint(int sig);
char *handl_comment(char *input);
int execution(char** input, cmd_t *cmd);
int check_dir_access(char **input, char* dir);

/* ------------------ENVIRONMENT----------------- */
char *_which(char *input);
int _env(char **input);
char *_getenv(const char *name);

/* ------------------BUILTINS----------------- */
/**
 * struct builtins - struct contain func name
 * @name: name of the function
 * @f: function to be called when name is invoked
 *
 * Description: struct of func name and its respective func
 */
typedef struct builtins
{
	char *name;
	int (*f)(char **input);
} built_t;

int parse_builtins(char **input, cmd_t *cmd);
int exit_sh(char **input, cmd_t *cmd);
int c_dir(char **input);
/*---change directory----*/
int cd_path(char *dir);
int cd_parent(void);
int cd_curr(void);
int cd_back(void);
int cd_home(void);

/* ------------------STRING PARSER----------------- */
int _isdigit(const char *str);
char **get_toks(char *args, char *delimiter);
void str_reverse(char *s);
char *_strdup(char *str);
int _strcmp(char *str_a, char *str_b);
char *_strcat(char *dest, char *src);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
int _atoi(char *s);
int is_cdir(char *path, int *i);

/* ------------------MEMORY----------------- */
void free_grid(char **grid, int height);
void free_cmd(cmd_t *cmd);
#endif /* SHELL_H */
