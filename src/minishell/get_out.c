/*
** get_out.c for  in /home/robin_l/Divers/42SH
** 
** Made by Loic Robin
** Login   <robin_l@epitech.net>
** 
** Started on  Thu May 21 00:03:27 2015 Loic Robin
** Last update Sat May 23 18:02:12 2015 Loic Robin
*/

#include <unistd.h>
#include "sh.h"

char		*get_out(t_dlist *lcmd, int n)
{
  char		*out;
  t_node	*tmp;

  out = NULL;
  if ((tmp = cursor_to_n(lcmd, n)) == NULL)
    return (NULL);
  tmp->token = DA;
  tmp = tmp->next;
  if (tmp == NULL || tmp->str == NULL)
    return (NULL);
  if (tmp->token == PATH)
    {
      if ((out = strcatrealloc(out, tmp->str, my_strlen(tmp->str))) == NULL)
	return (NULL);
      tmp->token = DA;
    }
  return (out);
}
