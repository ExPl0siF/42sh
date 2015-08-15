/*
** sh.h for  in /home/robin_l/Divers/42SH
** 
** Made by Loic Robin
** Login   <robin_l@epitech.net>
** 
** Started on  Sun May 10 21:47:44 2015 Loic Robin
** Last update Sat May 23 18:15:37 2015 Loic Robin
*/

#ifndef	_SH_H_
#define _SH_H_

#include <sys/types.h>
#include <unistd.h>
#include "list.h"
#include "my.h"
#include "config.h"

#define DELIM "<>|&;"
#define ERROR_MALLOC -6
#define INVALID_CMD -7
#define NB_OPERATOR 8
#define NB_BUILTIN 7

enum    typword
  {
    DA = 1,
    CMD,
    BUILTIN,
    PATH,
    SEMICOLON,
    LCHEV,
    LDCHEV,
    RCHEV,
    RDCHEV,
    PIPE,
    AND,
    OR,
    INGO,
    OUTGO
  };

typedef struct  s_lcmd  t_lcmd;
typedef	struct	s_shell	t_shell;
typedef	struct	s_exec	t_exec;
typedef	struct	s_cmd	t_cmd;
typedef struct	s_esc	t_esc;

struct          s_lcmd
{
  t_dlist       *cmd;
  int           tok_beg;
  int           retour;
  t_lcmd        *next;
};

struct		s_shell
{
  t_dlist	*lenv;
  char		**env;
  int		retour;
  int		fdout;
  int		quit;
  t_config	*config;
};

struct		s_esc
{
  char		*s;
  char		c;
};

struct		s_cmd
{
  int		type;
  int		retour;
  t_dlist	*lenv;
  char		*path;
  char		**env;
  char		**tabx;
  int		quit;
  int		fdout;
  int		fdrchev;
  int		fdlchev;
  int		error;
  int		ok;
};

struct		s_exec
{
  t_cmd		*cmd;
  pid_t		pid;
  t_dlist	*tmp_lenv;
  char		**tmp_env;
  int		tmp;
  int		status;
  int		token;
  int		pipe;
  int		npipe;
  int		endpipe;
  int		fd[2];
  int		lchev;
  int		rchev;
  int		fdrchev;
  int		fdin;
  int		fdout;
  int		stop;
};
int	nll;

void	init_sig();
void	inhib_signal();
void	newl();
void	show_token(int token);
void	error_open(char *path, int fd);
void	error_cmd(char *cmd, int fd, int type);
t_dlist	*env_in_list(char **env);
t_dlist	*mod_info_env(char *info, char *str, t_dlist *lenv);
t_dlist	*find_path_cmd(t_dlist *list, t_dlist *lenv);
int	check_lcmd(t_dlist *lcmd);
int	parse_lcmd(t_lcmd *lcmd, t_shell *sh);
int	get_cmd(t_dlist *lcmd, int *n, int max);
int	next_operator(t_dlist *lcmd, int *n, int max);
int	check_next_pipe(t_dlist *lcmd, int n, int max);
t_lcmd	*next_lcmd(t_lcmd *cursor, int retour);
int	nothing_to_do(t_dlist *lcmd, int n, int max);
char	*clean_word(char *str);
char	*get_out(t_dlist *lcmd, int n);
char	*get_info(char *type, t_dlist *lenv);
char	*get_path(char *cmd, char *path, int *ispath, t_dlist *lenv);
char	**list_in_env(char **env, t_dlist *lenv);
t_exec	*exec_builtin(t_exec *exec);
t_exec	*rchev_exec(t_exec *exec, t_dlist *lcmd, int n);
t_exec	*rdchev_exec(t_exec *exec, t_dlist *lcmd, int n);
t_exec	*lchev_exec(t_exec *exec, t_dlist *lcmd, int n, int *fdin);
t_exec	*ldchev_getin(t_exec *exec, char *in, int tmpfd[2], int pid);
t_exec	*ldchev_exec(t_exec *exec, t_dlist *lcmd, int n, int *fdin);
t_exec  *is_redir(t_exec *exec, t_dlist *lcmd, int n, int token);
t_exec  *set_exec(t_exec *exec, int *stop);
int     end_max_and_out(int redir, t_node *tmp, int n, int stop);
t_exec	*set_max_and_out(t_exec *exec, t_dlist *lcmd, int n, int *max);
t_cmd	*load_command_tab(t_cmd *cmd, t_dlist *lcmd, int n);
int	pipe_it(t_exec *exec);
int	fork_it(t_exec *exec);
int	built_or_exec(t_exec *exec);
t_exec	*process(t_exec *exec);
t_exec	*close_all(t_exec *exec);
int	set_stop_max_and_out(int redir, int token, int stop);
int	get_n_lchev(t_dlist *lcmd, int n);
t_node	*set_in_and_redir(t_node *in, t_node *tmp, int *redir);
t_node	*set_redir_in(t_node *in, int fdin, int *redir);
t_exec	*set_in(t_exec *exec, t_dlist *lcmd, int n);
int	get_fdin(t_dlist *lcmd, int n);
t_dlist	*lex_cmd(t_dlist *list, char *str);
t_dlist	*gere_path(t_dlist *list, char *str, int n);
t_lcmd	*surlex_cmd(t_lcmd *lcmd, t_dlist *cmd);
t_shell	*init_shell(t_shell *sh);
t_cmd	*init_cmd(t_cmd *cmd);
void	init_exec(t_exec *exec, t_shell *sh);
void	envvar_in_sh(t_list *, t_dlist *);
char	*prompt(char *, t_list *, t_list *);
t_dlist	*set_ali(t_list *, t_dlist *);
t_cmd	*my_echo_one(t_cmd *);

#endif	/* !_SH_H_ */
