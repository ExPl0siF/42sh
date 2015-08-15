/*
** list_pushbot.c for list in /home/closingin/Documents/Epitech/My/list
**
** Made by      Rémi WEISLINGER
** Login        closingin
**
** Started on   Jan 21 21:49 2015 closingin
** Update       May 19 10:14 2015 closingin
*/

#include <stdlib.h>
#include "config.h"

void		list_pushbot(t_list **list, void *data)
{
  t_list	*temp;
  t_list	*elem;

  if (!(elem = malloc(sizeof(t_list))))
    return ;
  elem->data = data;
  elem->next = NULL;
  elem->prev = NULL;
  if (!(*list))
    *list = elem;
  else
  {
    temp = *list;
    while ((*list)->next && (*list = (*list)->next));
    elem->prev = *list;
    elem->prev->next = elem;
    *list = temp;
  }
}
