#ifndef _SIMSHELL_H
#define _SIMSHELL_H


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <limits.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFSIZE 1024
#define TOK_DELIM " \t\r\n\a"
#define TOK_BUFSIZE 128


/**
 * struct data - structure containing all relevant data on runtime
 * @av: argument vector to be used
 * @input: command line inputted by user
 * @args: tokens used in the command line
 * @stat: last shell status
 * @count: lines counter
 * @_environ: environment variable
 * @pid: process ID of the shell
 */
typedef struct data
{
	char **args;
	int stat;
	char **av;
	char *input;
	int count;
	char **_environ;
	char *pid;
} data_shel;

/* Points to array of pointers to strings named the "environment" */
extern char **environ;

/**
 * struct sep_list_1 - single linked list
 * @separator: & | ;
 * @next: next node
 * Description: linked list to store separators
 */
typedef struct sep_list_1
{
	char separator;
	struct sep_list_1 *next;
} sep_list;

/**
 * struct line_list_1 - single linked list
 * @line: commandline
 * @next: next node
 * Description: single linked list keeping command lines
 */
typedef struct line_list_1
{
	char *line;
	struct line_list_1 *next;
} line_list;

/**
 * struct r_var_list_1 - single linked list
 * @len_var: variable length
 * @val: variable value
 * @len_val: length value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct r_var_list_1
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list_1 *next;
} r_var;

/**
 * struct builtin_1 - Builtin struct for command args.
 * @name: name of command builtin i.e env, exit, cd
 * @f: data type pointer function
 */
typedef struct builtin_1
{
	char *name;
	int (*f)(data_shel *datash);
} builtin_t;

/* ax_lists.c */
sep_list *add_sep_node(sep_list **head, char sep);
void frees_line_list(line_list **head);
line_list *add_line_node(line_list **head, char *line);
void free_sep_listt(sep_list **head);

/* ax_lists2.c */
r_var *add_var_node(r_var **head, int lenvar, char *var, int lval);
void free_var_list(r_var **head);

/* aux_str functions */
char *_strcat(char *destin, const char *src);
int _strsub(char *s, char *accept);
int _strcmp(char *str1, char *str2);
char *_strchar(char *s, char c);
char *_strcopy(char *destin, char *src);

/* aux_mem.c */
void _memcopy(void *newptr, const void *ptr, unsigned int size);
char **_relocdp(char **ptr, unsigned int old_size, unsigned int new_size);
void *_reloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* aux_str2.c */
char *_strdup(const char *s);
int _itsdigit(const char *s);
int cmp_char(char str[], const char *delimit);
int _strlength(const char *s);
char *_strtak(char str[], const char *delimit);

/* ax_str3.c */
void rev_str(char *s);

/* check_syntax_error.c */
int repeat_char(char *input, int a);
void print_error_syntax(data_shel *datash, char *input, int i, int bool);
int check_error_syntax(data_shel *datash, char *input);
int error_op(char *input, int a, char last);
int first_character(char *input, int *i);

/* shel_loop.c */
char *without_comment(char *inp);
void shel_loop(data_shel *datash);

/* read_line.c */
char *read_inline(int *i_eof);

/* split.c */
char *swap_chars(char *input, int bool);
char **split_lines(char *input);
void add_node(sep_list **head_s, line_list **head_l, char *input);
int split_command(data_shel *datash, char *input);
void go_nextt(sep_list **list_s, line_list **list_l, data_shel *datash);

/* rep_var.c */
void check_environ(r_var **h, char *in, data_shel *data);
char *replace_input(r_var **head, char *input, char *new_input, int nlength);
int check_var(r_var **h, char *in, char *st, data_shel *data);
char *repl_var(char *input, data_shel *datash);

/* get_line.c */
void bring_inline(char **lineptr, size_t *n, char *buffer, size_t q);
ssize_t get_inline(char **lineptr, size_t *n, FILE *stream);

/* exec_line */
int exec_inline(data_shel *datash);

/* cmd_exec.c */
int is_cd(char *path, int *i);
int cmd_execute(data_shel *datash);
char *_whichcmd(char *cmd, char **_environ);
int check_cmd_error(char *dir, data_shel *datash);
int is_exec(data_shel *datash);

/* env1.c */
char *_getenvi(const char *name, char **_environ);
int _env(data_shel *datash);

/* env2.c */
char *cpy_info(char *name, char *value);
void set_env(char *name, char *value, data_shel *datash);
int _setenvi(data_shel *datash);
int _unsetenvi(data_shel *datash);

/* cd.c */
void cd_to_hom(data_shel *datash);
void cd_dott(data_shel *datash);
void cd_prev(data_shel *datash);
void cd_tto(data_shel *datash);

/* cd_shell.c */
int cd_shel(data_shel *datash);

/* get_builtin */
int (*get_builtins(char *cmd))(data_shel *datash);

/* _exit.c */
int exit_shel(data_shel *datash);

/* aux_stdlib.c */
int get_length(int n);
int _atoi(char *s);
char *ax_itoa(int n);

/* aux_error1.c */
char *strcat_cdd(data_shel *, char *, char *, char *);
char *error_exit_shel(data_shel *datash);
char *errorr_not_found(data_shel *datash);
char *error_get_cdd(data_shel *datash);

/* aux_error2.c */
char *error_get_alias(char **args);
char *errorr_env(data_shel *datash);
char *error_syntax(char **args);
char *erorr_permission(char **args);
char *errorr_path_126(data_shel *datash);


/* get_error.c */
int get_errorr(data_shel *datash, int eval);

/* get_sigint.c */
void get_signalint(int sig);

/* aux_help.c */
void ax_help_env(void);
void ax_help_setenv(void);
void ax_help_unsetenv(void);
void ax_help_general(void);
void ax_help_exit(void);

/* aux_help2.c */
void ax_help(void);
void ax_help_alias(void);
void ax_help_cd(void);

/* get_help.c */
int get_helpp(data_shel *datash);

#endif
