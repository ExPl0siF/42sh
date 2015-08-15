/*
** surlex_cmd.c for  in /home/robin_l/Divers/42OOK
** 
** Made by Loic Robin
** Login   <robin_l@epitech.net>
** 
** Started on  Fri May 22 21:55:33 2015 Loic Robin
** Last update Fri May 22 21:56:16 2015 Loic Robin
*/

#include <stdlib.h>
#include <unistd.h>
#include "my.h"
#include "pars.h"
#include "sh.h"

t_lcmd  *create_lcmd(t_lcmd *new, int token)
{
  if ((new = malloc(sizeof(t_lcmd))) == NULL)
    return (NULL);
  if ((new->cmd = init_dlist(new->cmd)) == NULL)
    return (NULL);
  new->tok_beg = token;
  new->retour = 1;
  new->next = NULL;
  return (new);
}

t_lcmd          *under_surlex_cmd(t_lcmd *new, t_node *tmp, int *n)
{
  t_lcmd        *prev;
  t_node        *c;

  if ((tmp->token == SEMICOLON || tmp->token == OR || tmp->token == AND)
      && tmp->next != NULL)
    {
      *n = 0;
      prev = new;
      if ((new = create_lcmd(new, tmp->token)) == NULL)
        return (NULL);
      prev->next = new;
    }
  else if (tmp->token != SEMICOLON && tmp->token != OR && tmp->token != AND)
    {
      if ((new->cmd = insert_at_n(new->cmd, tmp->str, tmp->token, *n)) == NULL)
        return (NULL);
      if ((c = cursor_to_n(new->cmd, *n)) == NULL)
        return (NULL);
      if ((c->path = strcatrealloc(c->path, \
                                   tmp->path, my_strlen(tmp->path))) == NULL)
        return (NULL);
      *n += 1;
    }
  return (new);
}

t_lcmd          *surlex_cmd(t_lcmd *lcmd, t_dlist *cmd)
{
  t_node        *tmp;
  t_lcmd        *new;
  int           n;

  new = NULL;
  if ((new = create_lcmd(new, 0)) == NULL)
    return (NULL);
  lcmd = new;
  tmp = cmd->first;
  n = 0;
  while (tmp != NULL)
    {
      if ((new = under_surlex_cmd(new, tmp, &n)) == NULL)
        return (NULL);
      tmp = tmp->next;
    }
  return (lcmd);
}
