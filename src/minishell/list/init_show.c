/*
** init_show.c for  in /home/robin_l/Divers/Pushswap
** 
** Made by Loic Robin
** Login   <robin_l@epitech.net>
** 
** Started on  Fri Dec  5 21:32:23 2014 Loic Robin
** Last update Fri May 22 23:31:24 2015 Loic Robin
*/

#include <stdlib.h>
#include <unistd.h>
#include "list.h"
#include "sh.h"
#include "my.h"

void		show_dlist(t_dlist *list, int fd)
{
  t_node	*tmp;

  if (list == NULL)
    return;
  if (list->length == 0)
    {
      my_fdputstr("Environnement Vide\n", 2);
      return;
    }
  if ((tmp = list->first) == NULL)
    return;
  while (tmp != NULL)
    {
      my_fdputstr(tmp->str, fd);
      my_fdputchar('\n', fd);
      tmp = tmp->next;
    }
}

t_dlist	*init_dlist(t_dlist *list)
{
  list = NULL;
  if ((list = malloc(sizeof(t_dlist))) == NULL)
    return (NULL);
  list->length = 0;
  list->first = NULL;
  list->last = NULL;
  return (list);
}
