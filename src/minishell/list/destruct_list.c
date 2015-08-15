/*
** destruct_list.c for  in /home/robin_l/Divers/Pushswap/PushSwapN
** 
** Made by Loic Robin
** Login   <robin_l@epitech.net>
** 
** Started on  Sun Dec  7 19:31:46 2014 Loic Robin
** Last update Thu Feb  5 17:56:55 2015 Loic Robin
*/

#include <stdlib.h>
#include "../include/list.h"

void            destruct_dlist(t_dlist **list)
{
  t_node	*tmp;

  tmp = NULL;
  if ((*list) == NULL)
    return;
  if ((*list)->first != NULL)
    {
      tmp = (*list)->first;
      while (tmp->next != NULL)
	{
	  if (tmp->prev != NULL)
	      if (tmp->prev->str != NULL)
		free(tmp->prev->str);
	  if (tmp->prev != NULL)
	    free(tmp->prev);
	  tmp = tmp->next;
	}
      free(tmp->prev);
      free((*list)->last);
    }
  free((*list));
}

t_dlist		*destruct_last_node(t_dlist *list)
{
  t_node	*tmp_prev;

  if (list->last->str != NULL)
    free(list->last->str);
  list->last->str = NULL;
  if (list->first->next != NULL)
    {
      tmp_prev = list->last->prev;
      tmp_prev->next = NULL;
      free(list->last);
      list->last = tmp_prev;
    }
  else
    {
      free(list->last);
      list->first = NULL;
      list->last = NULL;
    }
  list->length -= 1;
  return (list);
}

t_dlist		*destruct_first_node(t_dlist *list)
{
  t_node	*tmp_next;

 if (list->first->str != NULL)
   free(list->first->str);
 list->first->str = NULL;
  if (list->first->next != NULL)
    {
      tmp_next = list->first->next;
      tmp_next->prev = NULL;
      free(list->first);
      list->first = tmp_next;
    }
  else
    {
      free(list->first);
      list->first = NULL;
      list->last = NULL;
    }
  list->length -= 1;
  return (list);
}

t_dlist		*destruct_center_node(t_dlist *list, int nb_node)
{
  t_node	*tmp_prev;
  t_node	*tmp_next;
  t_node	*tmp;

  tmp = NULL;
  if ((tmp = cursor_to_n(list, nb_node)) == NULL)
    return (NULL);
  tmp_next = tmp->next;
  tmp_prev = tmp->prev;
  tmp_next->prev = tmp_prev;
  tmp_prev->next = tmp_next;
  if (tmp->str != NULL)
    free(tmp->str);
  if (tmp != NULL)
    free(tmp);
  list->length -= 1;
  return (list);
}

t_dlist		*destruct_node(t_dlist *list, int nb_node)
{
  if (list == NULL || list->first == NULL)
    return (list);
  if (nb_node > list->length)
    return (list);
  else if (nb_node == 0)
    return (list = destruct_first_node(list));
  else if (nb_node == (list->length - 1))
    return (list = destruct_last_node(list));
  else
    return (list = destruct_center_node(list, nb_node));
}
