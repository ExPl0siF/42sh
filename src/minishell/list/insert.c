/*
** insert.c for  in /home/robin_l/Divers/Pushswap
** 
** Made by Loic Robin
** Login   <robin_l@epitech.net>
** 
** Started on  Fri Dec  5 21:34:21 2014 Loic Robin
** Last update Thu May 21 22:51:32 2015 Loic Robin
*/

#include <stdlib.h>
#include "../include/list.h"
#include "../include/my.h"

t_node          *cursor_to_n(t_dlist *list, int n)
{
  t_node        *tmp;
  int           i;

  i = 0;
  if (list == NULL)
    return (NULL);
  tmp = list->first;
  while (tmp != NULL && i < n)
    {
      tmp = tmp->next;
      i = i + 1;
    }
  return (tmp);
}

t_node	*get_position(t_dlist *list, t_node *node, int n)
{
  int	i;

  i = 1;
  if ((list->length / 2) > n)
    {
      i = 1;
      node = list->first;
      while (i < n && node != NULL)
	{
	  node = node->next;
	  i = i + 1;
	}
    }
  else
    {
      i = list->length;
      node = list->last;
      while (i > n && node != NULL)
	{
	  node = node->prev;
	  i = i - 1;
	}
    }
  return (node);
}

t_dlist		*insert_at_n(t_dlist *list, char *str, int token, int n)
{
  t_node	*node;
  t_node	*tmp_next;
  t_node	*tmp_prev;

  tmp_prev = NULL;
  if (list->first == NULL || n == 0)
    return (list = push_begin(list, str, token));
  if (list->length <= n || list->length == 1)
    return (list = push_end(list, str, token));
  if (n < 0 || ((node = malloc(sizeof(t_node))) == NULL))
    return (NULL);
  node->str = NULL;
  if ((node->str = strcatrealloc(node->str, str, my_strlen(str))) == NULL)
    return (NULL);
  node->ok = 1;
  node->token = token;
  node->path = NULL;
  tmp_prev = get_position(list, tmp_prev, n);
  tmp_next = tmp_prev->next;
  tmp_prev->next = node;
  node->prev = tmp_prev;
  node->next = tmp_next;
  tmp_next->prev = node;
  list->length += 1;
  return (list);
}

