/*
** is.c for config in /home/closingin/Documents/Epitech/Rendu/Unix/42sh/src/config
**
** Made by      Rémi Weislinger
** Login        closingin
**
** Started on   May 22 10:46 2015 closingin
** Update       May 23 11:36 2015 closingin
*/

#include <stdlib.h>
#include <stdio.h>
#include "config.h"
#include "my.h"

int		is_alias(char *s)
{
  int	ret;
  char	**w1;
  char	**w2;

  ret = 0;
  w1 = str_to_wordtab_delim(s, " \t");
  w2 = NULL;
  if (my_tablen(w1) >= 2 && !my_strcmp(w1[0], "alias"))
  {
    s += 5;
    while ((*s == ' ' || *s == '\t') && s++);
    my_free_wordtab(w1);
    w1 = str_to_wordtab_delim(s, "=");
    if (my_tablen(w1) >= 2 && my_str_isalnum_alias(w1[0]))
    {
      w2 = str_to_wordtab_delim(w1[1], " \t");
      if (my_tablen(w2) >= 1)
        ret = 1;
    }
  }
  my_free_wordtab(w1);
  my_free_wordtab(w2);
  return (ret);
}

int		is_var(char *s)
{
  int	ret;
  char	**w1;
  char	**w2;

  ret = 0;
  w1 = str_to_wordtab_delim(s, "=");
  w2 = NULL;
  if (my_tablen(w1) >= 2 && my_str_isalnum(w1[0]))
  {
    w2 = str_to_wordtab_delim(w1[1], " \t");
    if (my_tablen(w2) >= 1)
      ret = 1;
  }
  my_free_wordtab(w1);
  my_free_wordtab(w2);
  return (ret);
}

int		is_envvar(char *s)
{
  int	ret;
  char	**w1;
  char	**w2;

  ret = 0;
  w1 = str_to_wordtab_delim(s, " \t");
  w2 = NULL;
  if (my_tablen(w1) >= 2 && !my_strcmp(w1[0], "export"))
  {
    s += 6;
    while ((*s == ' ' || *s == '\t') && s++);
    my_free_wordtab(w1);
    w1 = str_to_wordtab_delim(s, "=");
    if (my_tablen(w1) >= 2 && my_str_isalnum(w1[0]))
    {
      w2 = str_to_wordtab_delim(w1[1], " \t");
      if (my_tablen(w2) >= 1)
        ret = 1;
    }
  }
  my_free_wordtab(w1);
  my_free_wordtab(w2);
  return (ret);
}
