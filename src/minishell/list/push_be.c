/*
** push_swap_be.c for  in /home/robin_l/Divers/Pushswap
** 
** Made by Loic Robin
** Login   <robin_l@epitech.net>
** 
** Started on  Fri Dec  5 21:00:00 2014 Loic Robin
** Last update Thu May 21 22:51:20 2015 Loic Robin
*/

#include <stdlib.h>
#include "../include/list.h"
#include "../include/my.h"

t_dlist		*push_begin(t_dlist *list, char *str, int token)
{
  t_node	*node;

  if ((node = malloc(sizeof(t_node))) == NULL || list == NULL)
    return (NULL);
  node->str = NULL;
  if ((node->str = strcatrealloc(node->str, str, my_strlen(str))) == NULL)
    return (NULL);
  node->ok = 1;
  node->path = NULL;
  node->token = token;
  node->prev = NULL;
  if (list->first != NULL)
    {
      list->first->prev = node;
      node->next = list->first;
    }
  else
    {
      node->next = NULL;
      list->last = node;
    }
  list->first = node;
  list->length += 1;
  return (list);
}

t_dlist		*push_end(t_dlist *list, char *str, int token)
{
  t_node	*node;

  if ((node = malloc(sizeof(t_node))) == NULL || list == NULL)
    return (NULL);
  node->str = NULL;
  if ((node->str = strcatrealloc(node->str, str, my_strlen(str))) == NULL)
    return (NULL);
  node->path = NULL;
  node->ok = 1;
  node->token = token;
  node->next = NULL;
  if (list->first != NULL)
    {
      list->last->next = node;
      node->prev = list->last;
    }
  else
    {
      list->first = node;
      node->prev = NULL;
    }
  list->last = node;
  list->length += 1;
  return (list);
}
