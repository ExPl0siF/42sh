/*
** list.c for 42sh in /home/therou-g/rendu/Unix/PSU_2014_42sh
**
** Made by Gaetan THEROU
** Login   <therou-g@epitech.net>
**
** Started on  Wed May  6 20:52:02 2015 Gaetan THEROU
** Last update Wed May 13 14:39:18 2015 Gaetan THEROU
*/

#include <stdlib.h>
#include <string.h>
#include <history.h>
#include <my.h>

t_history	*crea_list(char *cmd)
{
  t_history	*list;

  list = NULL;
  if (cmd != NULL)
  {
    if ((list = malloc(sizeof(t_history))) == NULL)
      return (NULL);
    list->cmd = my_strdup(cmd);
    list->next = NULL;
    list->prev = NULL;
  }
  return (list);
}

int		add_in_list(t_history *list, char *cmd)
{
  t_history	*new;

  while (list->next != NULL)
    list = list->next;
  if ((new = malloc(sizeof(t_history))) == NULL)
    return (-1);
  new->next = NULL;
  new->prev = list;
  if (new->prev != NULL)
  {
    if (my_strcmp(cmd, new->prev->cmd) != 0)
    {
      new->cmd = my_strdup(cmd);
      list->next = new;
      list = new;
    }
    else
      free(new);
  }
  return (0);
}

void	start(t_history **list)
{
  if ((*list) == NULL)
    return ;
  while ((*list)->prev != NULL)
    (*list) = (*list)->prev;
}

void	end(t_history **list)
{
  if ((*list) == NULL)
    return ;
  while ((*list)->next != NULL)
    (*list) = (*list)->next;
}

void	display_history(t_history *list)
{
  int	i;

  i = 0;
  if (list == NULL)
    return ;
  start(&list);
  while (list != NULL)
    {
      my_printf("cmd[%d]-> %s\n", i++, list->cmd);
      list = list->next;
    }
  return ;
}
