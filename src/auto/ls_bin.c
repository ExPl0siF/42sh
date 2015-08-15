/*
** main.c for  in /home/ExPl0siF/Bin/base_directory
**
** Made by Theo Caselli
** Login   <casell_t@epitech.net>
**
** Started on  Wed May  6 13:34:46 2015 Theo Caselli
** Last update Fri May 22 15:17:13 2015 Theo Caselli
*/

#include <sys/types.h>
#include <termios.h>
#include <ncurses.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <term.h>
#include <history.h>
#include <dtab.h>
#include <my.h>

char    *add_slash_check(char *str, char *buff)
{
  char  *res;

  res = NULL;
  res = strcatrealloc(res, str, my_strlen(str));
  res = strcatrealloc(res, "/\0", 1);
  res = strcatrealloc(res, buff, my_strlen(buff));
  return (res);
}

int   	check_binaire(char **path, char *cmd, t_lol *l_tab)
{
  int  	i;
  int	j;

  i = -1;
  j = 0;
  while (path[++i] != NULL)
    {
      path[i] = add_slash_check(path[i], cmd);
      j += my_ls(path[i], l_tab);
    }
  return ((j == 0) ? (-1) : (0));
}
