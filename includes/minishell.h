#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft.h"
#include "readline.h"
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/wait.h>
#include <limits.h>
#include <errno.h>
#include <signal.h>
#include <sys/stat.h>

/*
** token types 
*/

#define EMPTY 0
#define CMD 1
#define ARG 2
#define TRUNC 3
#define APPEND 4
#define INPUT 5
#define PIPE 6
#define END 7

#define SKIP 1
#define NOSKIP 0

/*
** standar input putput error 
*/

#define EXPANSION -1

#define STDIN 0
#define STDOUT 1
#define STDERR 2

/*
** return value of exucuted commands
*/

#define ERROR 1
#define SUCCESS 0
#define IS_DIRECTORY 126
#define UNKNOWN_COMMAND 127

/*
** maximun size of cwd string 
*/

#define BUFF_SIZE 4096

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

/*
** colors
*/

#define RESET "\033[0m"
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define BOLDBLACK "\033[1m\033[30m"
#define BOLDRED "\033[1m\033[31m"
#define BOLDGREEN "\033[1m\033[32m"
#define BOLDYELLOW "\033[1m\033[33m"
#define BOLDBLUE "\033[1m\033[34m"
#define BOLDMAGENTA "\033[1m\033[35m"
#define BOLDCYAN "\033[1m\033[36m"
#define BOLDWHITE "\033[1m\033[37m"

#define DQOUTE 2
#define QOUTE 1

/*
** typedef
*/

typedef struct s_expansions
{
	char *new_arg;
	int i;
	int j;
} t_expansions;

typedef struct s_sl
{
	char *buf;
	char *shlvl;
	int shl;
	int i;
	char cwd[PATH_MAX];
} t_sl;

typedef struct s_token
{
	char *str;
	int type;
	struct s_token *prev;
	struct s_token *next;
} t_token;

typedef struct s_env
{
	char *value;
	struct s_env *next;
} t_env;

typedef struct s_sig
{
	int exit_status;
	pid_t pid;
} t_sig;


typedef struct s_ms
{
	char prompt[17];
	char *line;
	t_env *env;
	t_token *token;
	int exit;
	int in;
	int out;
	int ret;
	int fdin;
	int fdout;
	int pipin;
	int pipout;
	int pid;
	int charge;
	int parent;
	int last;
	int no_exec;
	t_list *hist;
	int	h_fd;
} t_ms;


/*
** EXEC
*/
int exec_bin(char **args, t_env *env, t_ms *ms);
int exec_builtin(t_ms *ms, char **args);
int is_builtin(char *command);

/*
** BUILTINS
*/

int ft_echo(t_ms *ms, char **args);
int ft_cd(t_env *env, char **args);
int ft_pwd(t_ms *ms, char **args);
int ft_export(t_env *env, char **args);
void export_env(t_env *env, char *key, int len);

void ft_env(t_env *env);
void ms_exit(t_ms *ms, char **cmd);
int ft_unset(t_ms *ms, char **args);

/*
** env
*/

t_env *new_env(char *value);
void add_env(t_env *env, char *value);
void init_env(t_ms *ms, char **env);
int env_len(char *s);
void del_node(t_env **env, t_env *node);
void free_node(t_env *node);
char *env_value(t_env *env, char *key);
char *env_to_str(t_env *lst);
size_t size_env(t_env *lst);
char **lst_to_tab(t_env *lst);

/*
** parsnig
*/
void export_env(t_env *env, char *key, int len);
void parse(t_ms *ms);
int is_sep(char *line, int i);
int ignore_sep(char *line, int i);
int quotes(char *line, int index);
int quote_check(t_ms *ms, char *line);
char *space_alloc(char *line);
char *sep_space(char *line);
t_token *get_tokens(char *line);
void ft_skip_space(const char *str, int *i);
t_token *next_token(char *line, int *i);
void type_arg(t_token *token, int separator);
int token_len(char *line, int *i);
void print_token(t_token *t);
void ft_close(int fd);
void reset_std(t_ms *ms);
void close_fds(t_ms *ms);
void reset_fds(t_ms *ms);
t_token *next_sep(t_token *token, int skip);
t_token *prev_sep(t_token *token, int skip);
t_token *next_run(t_token *token, int skip);
int is_type(t_token *token, int type);
int is_types(t_token *token, char *types);
int has_type(t_token *token, int type);
int has_pipe(t_token *token);
t_token *next_type(t_token *token, int type, int skip);
void redir(t_ms *ms, t_token *token, int type);
void input(t_ms *ms, t_token *token);
int ft_pipe(t_ms *ms);

// void free_tab(char **args);
void exec_cmd(t_ms *ms, t_token *token);
char *expansions(char *arg, t_env *env, int ret);
void free_token(t_ms *ms);
int ret_size(int ret);
int get_var_len(const char *arg, int pos, t_env *env, int ret);
int arg_alloc_len(const char *arg, t_env *env, int ret);
char *get_var_value(const char *arg, int pos, t_env *env, int ret);
static int varlcpy(char *new_arg, const char *env_value, int pos);
static void insert_var(t_expansions *ex, char *arg, t_env *env, int ret);
char *expansions(char *arg, t_env *env, int ret);
int is_env_char(int c);
int is_valid_env(const char *env);
int env_value_len(const char *env);
char *value_env(char *env);
char *get_env_value(char *arg, t_env *env);
void ms_exit(t_ms *ms, char **cmd);
void sig_init(void);
void sig_quit(int code);
void sig_int(int code);
void ft_prompt(int ret);
void las_cmd(t_ms *ms, char **args);
void sort_args(t_ms *ms);
int is_last_valid_arg(t_token *token);
int update_oldpwd(t_env *env);
int update_pwd(t_env *env);
int go_to_path(int option, t_env *env);


t_sig g_sig;


#endif