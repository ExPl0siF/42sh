/*
** find_history.c for find_history in /home/slv_prometheen/PSU_2014_42sh/src/history
**
** Made by Anthony KONDRATUK
** Login   <slv_prometheen@epitech.net>
**
** Started on  Tue May 12 15:02:14 2015 Anthony KONDRATUK
** Last update Sat May 23 14:29:08 2015 Loic Robin
*/

#include <stdlib.h>
#include <history.h>
#include <my.h>

char	*find_in_history(t_history *list, int nb)
{
  char	*str;
  int	i;

  i = 1;
  str = NULL;
  end(&list);
  if (list == NULL)
    return (NULL);
  if (i == nb)
    str = my_strdup(list->cmd);
  while ((i < nb) && (list->prev != NULL))
    {
      i++;
      str = my_strdup(list->cmd);
      list = list->prev;
    }
  return (str);
}

char	*find_last_history(t_history *list)
{
  end(&list);
  return (list->cmd);
}

char	*find_last(t_history *list, char *comp)
{
  end(&list);
  while (my_strncmp(list->cmd, comp + 1, my_strlen(comp) - 1))
    list = list->prev;
  return (list->cmd);
}
