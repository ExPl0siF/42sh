/*
** gere_path.c for  in /home/robin_l/Divers/42OOK
** 
** Made by Loic Robin
** Login   <robin_l@epitech.net>
** 
** Started on  Fri May 22 21:51:19 2015 Loic Robin
** Last update Fri May 22 21:52:01 2015 Loic Robin
*/

#include <stdlib.h>
#include <unistd.h>
#include "my.h"
#include "pars.h"
#include "sh.h"

t_dlist         *gere_path(t_dlist *list, char *str, int n)
{
  char          *path;
  char          *cmd;
  int           p;
  int           s;

  path = NULL;
  p = -1;
  while (str[++p] != '\0' && is_delim(str[p], " \t") == 0);
  if (p > 0)
    if ((path = strcatrealloc(path, str, p)) == NULL)
      return (NULL);
  cmd = NULL;
  s =  my_strlen(&(str[p]));
  if (s > 0)
    if ((cmd = strcatrealloc(cmd, &(str[p + 1]), s)) == NULL)
      return (NULL);
  if ((list = destruct_node(list, n)) == NULL)
    return (NULL);
  if (s > 0)
    if ((list = insert_at_n(list, cmd, CMD, n)) == NULL)
      return (NULL);
  if (path != NULL)
    if ((list = insert_at_n(list, path, PATH, n)) == NULL)
      return (NULL);
  return (list);
}

t_dlist         *find_path_cmd(t_dlist *list, t_dlist *lenv)
{
  t_node        *tmp;
  char          *str;
  int           ok;
  int           p;

  tmp = list->first;
  while (tmp != NULL)
    {
      tmp->path = NULL;
      if (tmp->token == CMD && tmp->str != NULL)
        {
          p = -1;
          str = NULL;
          while (tmp->str[++p] != '\0' && is_delim(tmp->str[p], " \t") == 0);
          if (p > 0)
            if ((str = strcatrealloc(str, tmp->str, p)) == NULL)
              return (NULL);
          ok = 0;
          if (!(tmp->path = get_path(str, tmp->path, &ok, lenv)) || ok == 0)
            tmp->path = NULL;
          tmp->ok = ok;
        }
      tmp = tmp->next;
    }
  return (list);
}
