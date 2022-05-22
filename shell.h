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
#define MAXARGS 128
#define DELIM " \t\n\r\a"

extern char **environ;

/**
 * struct cmd_t - shell env vars
 * @mode: determines the mode of execution
 * @args: the arguments to be executed
 * @ready: determines if the shell should run.
 * @status: the status of the last command executed.
 * @av: the argv array
 * @counter: the number of loops.
 * @pid: the pid of the last command executed.
 * @input: the input commands.
 * @envar: the environment variables.
 *
 * Description: Struct contain all shell vars.
 */
typedef struct cmd_t
{
	int mode;
	char *input;
	char **args;
	int ready;
	int status;
	char **envar;
	int counter;
	char **av;
	char *pid;
} cmd_t;

void open_console(void);
void init_cmd(cmd_t *cmd, char **av);
void prompt(int status);
void t_error(char *s);
int _fork(void);
void setcmd(char *buf, cmd_t *cmd);
void *_realloc(void *ptr, size_t old_size, size_t new_size);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);
char *_readwrite(int status, int *is_eof);
void runcmd(char *dir, char **input, cmd_t *cmd);
ssize_t _getline(char **line_ptr, size_t *n, FILE *stream);
char *_strtok(char *strn, const char *delim);
void handl_sigint(int sig);
char *handl_comment(char *input);
int execution(cmd_t *cmd);
void rep_loop(cmd_t *cmd);
int cmd_exec(cmd_t *cmd);
int check_dir_access(char *dir, cmd_t *cmd);
int apply_seperators(cmd_t *cmd, char *input);

/* ------------------ENVIRONMENT----------------- */
char *_which(char *cmd, char **_environ);
int _env(cmd_t *cmd);
char *_getenv(const char *name, char **_environ);

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
	int (*f)(cmd_t *cmd);
} built_t;

int parse_builtins(cmd_t *cmd);
int exit_sh(cmd_t *cmd);
int c_dir(cmd_t *cmd);
int _setenv(cmd_t *cmd);
void set_env(char *name, char *value, cmd_t *cmd);
int _unsetenv(cmd_t *cmd);
int get_help(cmd_t *cmd);
/*---change directory----*/
int cd_path(char *dir, cmd_t *cmd);
int cd_parent(cmd_t *cmd);
int cd_curr(cmd_t *cmd);
int cd_back(cmd_t *cmd);
int cd_home(cmd_t *cmd);

/* ----------------LINKEDLIST ------------ */
/**
 * struct list_s - linked list
 * @var_len: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct list_s
{
	int var_len;
	char *val;
	int len_val;
	struct list_s *next;
} list_t;

/**
 * struct sep_s - single linked list
 * @sep: serperator (; or | or &)
 * @next: pointer to next node
 * Description: linked list holding the seperators
 */
typedef struct sep_s
{
	char sep;
	struct sep_s *next;
} sep_t;

/**
 * struct line_s - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct line_s
{
	char *line;
	struct line_s *next;
} line_t;

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
int (*get_builtin(char *input))(cmd_t *);
char *parse_input(char *input, cmd_t *cmd);
char *replaced_input(list_t **head, char *input, char *new_input, int nlen);
int scan_vars(list_t **h, char *input, char *status, cmd_t *cmd);
void evar_check(list_t **head, char *input, cmd_t *cmd);
int get_len(int n);
char *_itoa(int n);
char *copy_info(char *name, char *value);

/* ------------------MEMORY----------------- */
void free_grid(char **grid, int height);
void free_cmd(cmd_t *cmd);

/* aux_lists.c */
sep_t *add_sep_node_end(sep_t **head, char sep);
void free_sep_list(sep_t **head);
line_t *add_line_node_end(line_t **head, char *line);
void free_line_list(line_t **head);

/* aux_lists2.c */
list_t *add_node_end(list_t **head, int var_len, char *val, int len_val);
void free_list(list_t **head);

/* aux_help.c */
void aux_help_env(void);
void aux_help_setenv(void);
void aux_help_unsetenv(void);
void aux_help_general(void);
void aux_help_exit(void);

/* aux_help2.c */
void aux_help(void);
void aux_help_alias(void);
void aux_help_cd(void);

/* get_help.c */
int get_help(cmd_t *cmd);

/* check_syntax_error.c */
int repeated_char(char *input, int i);
int error_sep_op(char *input, int i, char last);
int first_char(char *input, int *i);
void print_syntax_error(cmd_t *cmd, char *input, int i, int bool);
int check_syntax_error(cmd_t *cmd, char *input);


#endif /* SHELL_H */
