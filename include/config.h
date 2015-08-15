/*
** config.h for include in /home/closingin/Documents/Epitech/Rendu/Unix/42sh/include
**
** Made by      Rémi Weislinger
** Login        closingin
**
** Started on   May 19 10:08 2015 closingin
** Update       May 24 14:27 2015 closingin
*/

#ifndef CONFIG_H_
# define CONFIG_H_

#define CONFIG_FILE	".42shrc"

typedef struct	s_list
{
  void		*data;
  struct s_list	*next;
  struct s_list	*prev;
}		t_list;

typedef struct	s_config
{
  t_list       	*file;
  t_list       	*aliases;
  t_list       	*vars;
  t_list       	*envvars;
}	       	t_config;

typedef struct	s_file
{
  char	       	*content;
  int  		line;
}    	       	t_file;

typedef struct	s_alias
{
  char		*name;
  char	       	*cmd;
}    		t_alias;

typedef struct	s_var
{
  char	       	*name;
  char	       	*content;
}		t_var;

int				is_alias(char *);
int				is_var(char *);
int				is_envvar(char *);

int				parse_alias(char *, t_list **);
int				parse_var(char *, t_list **);
int				parse_envvar(char *, t_list **);

int				check_exist_alias(t_alias *, t_list *);
int				check_exist_var(t_var *, t_list *);

void			list_pushbot(t_list **, void *);
char			*my_strinit(int);
int				my_tablen(char **);
int				my_free_wordtab(char **);
int				my_str_isalnum(char *);
int				my_str_isalnum_alias(char *);

void			parse_rc(t_config *);
int				open_rc(char *);
t_list			*load_rc(int);
t_config		*init_rc(char *);

#endif /* !CONFIG_H_ */
