/*
** global.c for  in /home/ExPl0siF/Rendu/PSU_2014_42sh
**
** Made by Theo Caselli
** Login   <casell_t@epitech.net>
**
** Started on  Sun May 24 15:02:00 2015 Theo Caselli
** Last update Sun May 24 15:06:16 2015 Theo Caselli
*/

#include <sys/types.h>
#include <termios.h>
#include <ncurses.h>
#include <dirent.h>
#include <string.h>
#include <term.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <glob.h>
#include "get_next_line.h"
#include "dtab.h"
#include "my.h"
#include "pars.h"
#include "sh.h"
#include "history.h"

char	*first_pars(char *str, t_save_pos_i *save_pos_i)
{
  int	i;
  char	*tmp;

  tmp = NULL;
  i = -1;
  if (my_strstrint(str, "*") == 1)
    {
      while (str[++i] != '*');
      save_pos_i->save_pos = i;
      while (str[i] != '\0' && str[i] != ' ' && str[i] != '|' && str[i] != ';'
	     && str[i] != '>' && str[i] != '&' && str[i] != '<'
	     && str[i] != '[' && str[i] != ']')
	i++;
      tmp = save_util(str, i);
    }
  save_pos_i->i = i;
  return (tmp);
}

char	*replace_str(char *repl_str, glob_t *global, size_t lo)
{
  while (++lo != global->gl_pathc)
    {
      repl_str = strcatrealloc(repl_str, global->gl_pathv[lo],
			       my_strlen(global->gl_pathv[lo]));
      repl_str = strcatrealloc(repl_str, " ", 1);
    }
  return (repl_str);
}

char		*check_star(t_save_pos_i *save_pos_i, glob_t *global,
			    char *str, char *tmp_three)
{
  size_t	lo;
  char		*tmp_two;
  char		*repl_str;

  lo = -1;
  tmp_two = NULL;
  repl_str = NULL;
  repl_str = replace_str(repl_str, global, lo);
  if (save_pos_i->save_pos != 0)
    {
      while (save_pos_i->save_pos != 0 && str[save_pos_i->save_pos] != ' '
	     && str[save_pos_i->save_pos] != '|' && str[save_pos_i->save_pos] != ';'
	     && str[save_pos_i->save_pos] != '>' && str[save_pos_i->save_pos] != '&'
	     && str[save_pos_i->save_pos] != '<' && str[save_pos_i->save_pos] != '['
	     && str[save_pos_i->save_pos] != ']')
	save_pos_i->save_pos--;
      save_pos_i->save_pos++;
      tmp_two = strcatrealloc(tmp_two, str, save_pos_i->save_pos);
      tmp_two = strcatrealloc(tmp_two, repl_str, my_strlen(repl_str));
      tmp_two = strcatrealloc(tmp_two, tmp_three, my_strlen(tmp_three));
    }
  else
    tmp_two = strcatrealloc(tmp_two, repl_str, my_strlen(repl_str));
  free(repl_str);
  return (tmp_two);
}

char	*rempl_tmp_three(char *tmp_three, char *str_read,
			 t_save_pos_i *save_pos_i)
{
  if (my_strlen(str_read) <= 3 && str_read[0] == '*' && str_read[1] == '.')
    tmp_three = strcatrealloc(tmp_three, &str_read[save_pos_i->save_pos],
			      my_strlen(&str_read[save_pos_i->save_pos]));
  else
    tmp_three = strcatrealloc(tmp_three, &str_read[save_pos_i->i],
			      my_strlen(&str_read[save_pos_i->i]));
  return (tmp_three);
}

char		*replace_star(char *str_read)
{
  char		*res;
  char		*tmp;
  char		*tmp_three;
  glob_t	*global;
  t_save_pos_i	save_pos_i;

  tmp = NULL;
  tmp_three = NULL;
  if ((global = malloc(sizeof(glob_t))) == NULL)
    return (str_read);
  tmp = first_pars(str_read, &save_pos_i);
  if (tmp != NULL)
    {
      tmp_three = rempl_tmp_three(tmp_three, str_read, &save_pos_i);
      glob(tmp, GLOB_DOOFFS && GLOB_APPEND, NULL, global);
      res = check_star(&save_pos_i, global,
		       str_read, tmp_three);
      globfree(global);
      if (res != NULL || my_strlen(res) != 0)
	return (res);
    }
  free(tmp_three);
  free(tmp);
  return (str_read);
}
