/*
** my.h for  in /home/casell_t/rendu/Piscine_C_J09/include
**
** Made by Theo Caselli
** Login   <casell_t@epitech.net>
**
** Started on  Thu Oct  9 10:41:40 2014 Theo Caselli
** Last update Sun May 24 15:05:48 2015 Theo Caselli
*/

#ifndef DTAB_H_
#define DTAB_H_

#include <sys/types.h>
#include <termios.h>
#include <ncurses.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>
#include <term.h>
#include <history.h>
#include <my.h>

typedef struct	s_tab
{
  int		nb_item;
  char		*cmd;
  struct s_tab 	*next;
  struct s_tab 	*prev;
}		t_tab;

typedef struct	s_lol
{
  int		nb_item;
  DIR		*dir;
  t_tab		*list;
}		t_lol;

typedef struct	s_save_pos_i
{
  int		i;
  int		save_pos;
}		t_save_pos_i;

int	check_point(char *tmp);
int	my_ls(char *buff, t_lol *l_tab);
int	check_occ(t_lol *l_tab, char *cmd);
int	my_strstrint(char *str, char *to_find);
int	add_maillon(t_tab *list, char *cmd, int nb);
int	my_ls_two(char *tmp, char *buff, t_lol *l_tab);
int	check_binaire(char **path, char *cmd, t_lol *l_tab);
int	recup_key(char **tab_path, char *home, t_caps *save, t_lol *l_tab);
int	my_ls_three(char *buff, t_lol *l_tab, int k, struct dirent *ent);
DIR	*chefol(char *buff, int i);
DIR	*open_direct(char *buff, int i, DIR *dir);
char	*rm_n(char *buff);
char    *reset_buff(char *buff, char *home);
char	*save_util(char *str, int pos);
char	*add_slash_check(char *str, char *buff);
char	*first_pars(char *str, t_save_pos_i *save_pos_i);
char	*replace_str(char *repl_str, glob_t *global, size_t lo);
char	*check_star(t_save_pos_i *save_pos_i, glob_t *global,
		    char *str, char *tmp_three);
char	*rempl_tmp_three(char *tmp_three, char *str_read,
			 t_save_pos_i *save_pos_i);
char	*replace_star(char *str_read);
void	aff_list(t_lol *l_tab);
void	check_list(t_lol *l_tab, char *cmd, int nb, char *buff);
int	check_fold(char *cmd, char *buff);
t_tab	*list_create(char *cmd, int nb);
void	multi_posi(t_lol *);
char	find_next_char(int, t_lol *);
int	my_strlen_buff(char *);
void	exec_auto(t_caps *, t_lol *);
void	start_tab(t_tab **);
void    recup_key_two(char **tab_path, char *home, char *buff, t_lol *l_tab);

#endif /* !_DTAB_H */
