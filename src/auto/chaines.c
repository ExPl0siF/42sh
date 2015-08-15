/*
** chaines.c for try lists in /home/slv_prometheen/Rendu/dtab/src
**
** Made by Anthony KONDRATUK
** Login   <slv_prometheen@epitech.net>
**
** Started on  Wed May 13 12:57:31 2015 Anthony KONDRATUK
** Last update Fri May 22 11:37:34 2015 Theo Caselli
*/

#include <sys/types.h>
#include <termios.h>
#include <ncurses.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <term.h>
#include <dtab.h>
#include <my.h>

t_tab  	*list_create(char *cmd, int nb)
{
  t_tab	*list;
  t_tab	*new;

  new = NULL;
  list = NULL;
  if (cmd != NULL)
    {
      if ((new = malloc(sizeof(t_tab))) == NULL)
        return (NULL);
      new->cmd = my_strdup(cmd);
      new->nb_item = nb;
      new->next = NULL;
      new->prev = list;
      if (list != NULL)
        list->next = new;
      list = new;
    }
  return (list);
}

int	add_maillon(t_tab *list, char *cmd, int nb)
{
  t_tab	*new;

  while (list->next != NULL)
    list = list->next;
  if ((new = malloc(sizeof(t_tab))) == NULL)
    return (-1);
  new->next = NULL;
  new->prev = list;
  list->next = new;
  new->cmd = my_strdup(cmd);
  new->nb_item = nb;
  return (0);
}

int	check_occ(t_lol *l_tab, char *cmd)
{
  while (l_tab->list->prev != NULL)
    l_tab->list = l_tab->list->prev;
  while (l_tab->list->next != NULL)
    {
      if (strcmp(l_tab->list->cmd, cmd) == 0)
	return (1);
      l_tab->list = l_tab->list->next;
    }
  return (0);
}

void	check_list(t_lol *l_tab, char *cmd, int nb, char *buff)
{
  char	*str;

  str = NULL;
  str = strcatrealloc(str, cmd, my_strlen(cmd));
  if (l_tab->list == NULL)
    {
      if (check_fold(str, buff) == 0)
        str = strcatrealloc(str, "/", 1);
      if (strcmp(str, "./") != 0 && strcmp(str, "../") != 0)
	{
	  l_tab->list = list_create(str, nb);
	  l_tab->nb_item++;
	}
    }
  else
    if (check_occ(l_tab, str) != 1)
      {
	if (check_fold(str, buff) == 0)
	  str = strcatrealloc(str, "/", 1);
	if (strcmp(str, "./") != 0 && strcmp(str, "../") != 0)
	  {
	    add_maillon(l_tab->list, str, nb);
	    l_tab->nb_item++;
	  }
      }
}
