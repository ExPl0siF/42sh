/*
** main.c for  in /home/ExPl0siF/Bin/base_directory
**
** Made by Theo Caselli
** Login   <casell_t@epitech.net>
**
** Started on  Wed May  6 13:34:46 2015 Theo Caselli
** Last update Sun May 24 00:00:47 2015 Theo Caselli
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

char	*rm_n(char *buff)
{
  int	i;

  i = -1;
  while (buff[++i] != '\0')
    if (buff[i] == 10)
      buff[i] = 0;
  return (buff);
}

int	check_point(char *tmp)
{
  int	i;

  i = -1;
  while (tmp[++i] != '\0')
    if (tmp[i] != '.' && tmp[i] != '/')
      return (-1);
  return (0);
}

char	*save_util(char *str, int pos)
{
  int	i;
  char	*buff;

  i = 0;
  if ((buff = malloc(pos + 2)) == NULL)
    return (NULL);
  pos--;
  while (str[pos] != ' ' && str[pos] != '|' && str[pos] != ';'
	 && str[pos] != '>' && str[pos] != '&' && str[pos] != '<'
	 && str[pos] != '[' && str[pos] != ']')
    {
      if (str[pos] == 0)
	pos--;
      buff[i] = str[pos];
      i++;
      pos--;
      if (pos == -1)
	break;
    }
  buff[i] = 0;
  buff = my_revstr(buff);
  return (buff);
}

void	aff_list(t_lol *l_tab)
{
  if (l_tab->list != NULL)
    {
      while (l_tab->list->prev != NULL)
	l_tab->list = l_tab->list->prev;
      while (l_tab->list->next != NULL)
	{
	  l_tab->list = l_tab->list->next;
	  my_printf("%s\n", l_tab->list->cmd);
	}
      if (l_tab->nb_item == 1)
	my_printf("%s\n", l_tab->list->cmd);
    }
}

char	*reset_buff(char *buff, char *home)
{
  char	*save;

  save = NULL;
  save = strcatrealloc(save, &buff[2], my_strlen(&buff[2]));
  if (buff != NULL)
    free(buff);
  buff = NULL;
  buff = strcatrealloc(buff, home, my_strlen(home));
  buff = strcatrealloc(buff, "/\0", 1);
  buff = strcatrealloc(buff, save, my_strlen(save));
  return (buff);
}
