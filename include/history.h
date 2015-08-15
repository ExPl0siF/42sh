/*
** history.h for  in /home/therou-g/rendu/Unix/PSU_2014_42sh
**
** Made by Gaetan THEROU
** Login   <therou-g@epitech.net>
**
** Started on  Wed May  6 19:57:41 2015 Gaetan THEROU
** Last update Sat May 23 17:36:13 2015 Loic Robin
*/

#ifndef HISTORY_H_
# define  HISTORY_H_

#include <termios.h>
#include <curses.h>
#include <term.h>
#include <list.h>

#define LEN_HIST 50
#define TOP 65
#define BOT 66
#define LEFT 68
#define RIGHT 67
#define HIST_FILE ".42sh_history"

typedef struct		s_history
{
  char			*cmd;
  int			new_elem;
  struct s_history	*next;
  struct s_history	*prev;
}			t_history;

typedef struct	s_caps
{
  char		*prompt;
  char		*cmd;
  char		*save_cmd;
  char		buff[4];
  int		pos_hist;
  int		cursor_pos;
  int		nb_tab;
  struct termios	term;
  struct termios	save;
  int		ok;
  t_dlist	*lenv;
  t_history	*hist;
}		t_caps;

int		my_put_getstr(int);
void		aff_cmd(t_caps *);
char		*put_char_str(char *, char, int);
t_history	*add_history(t_history *, char *);
char		*my_strdup(char *);
void		buff_read_cmd(t_caps *);
char		*find_in_history(t_history *, int);
void		exec_arrow(t_caps *);
void		end(t_history **);
t_history       *crea_list(char *);
int             add_in_list(t_history *, char *);
char		*save_buff(char *, int);
char		*my_delete_char(t_caps *);
char		*my_read(t_caps *);
void		init_history(t_caps *);
void		init_tcaps(t_caps *, t_dlist *);
void		write_history(t_history *);

#endif /* !HISTORY */
