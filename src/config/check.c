/*
** check.c for config in /home/closingin/Documents/Epitech/Rendu/Unix/42sh/src/config
**
** Made by      Rémi Weislinger
** Login        closingin
**
** Started on   May 24 14:15 2015 closingin
** Update       May 24 14:31 2015 closingin
*/

#include <stdlib.h>
#include <string.h>
#include "config.h"

int			check_exist_alias(t_alias *alias, t_list *aliases)
{
  t_alias	*tmp;

  while (aliases)
  {
    tmp = (t_alias *)aliases->data;
    if (!strcmp(tmp->name, alias->name))
    {
      free(tmp->cmd);
      tmp->cmd = strdup(alias->cmd);
      free(alias->name);
      free(alias->cmd);
      free(alias);
      return (1);
    }
    aliases = aliases->next;
  }
  return (0);
}

int			check_exist_var(t_var *var, t_list *vars)
{
  t_var		*tmp;

  while (vars)
  {
    tmp = (t_var *)vars->data;
    if (!strcmp(tmp->name, var->name))
    {
      free(tmp->content);
      tmp->content = strdup(var->content);
      free(var->name);
      free(var->content);
      free(var);
      return (1);
    }
    vars = vars->next;
  }
  return (0);
}
