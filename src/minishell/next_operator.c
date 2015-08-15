/*
** next_operator.c for  in /home/robin_l/Divers/42OOK
** 
** Made by Loic Robin
** Login   <robin_l@epitech.net>
** 
** Started on  Fri May 22 22:12:57 2015 Loic Robin
** Last update Sat May 23 18:03:04 2015 Loic Robin
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include "pars.h"
#include "my.h"

int             get_cmd(t_dlist *lcmd, int *n, int max)
{
  t_node        *tmp;
  int           ntmp;
  int           tok;

  if ((tmp = cursor_to_n(lcmd, *n)) == NULL)
    return (-1);
  ntmp = *n;
  tok = CMD;
  while (tmp != NULL && ntmp <= max)
    {
      if (tmp->token == tok || tmp->token == BUILTIN)
        {
          *n = ntmp;
          return (tok);
        }
      ntmp += 1;
      tmp = tmp->next;
    }
  return (0);
}

int		next_operator(t_dlist *lcmd, int *n, int max)
{
  t_node	*tmp;
  int           ntmp;

  if ((tmp = cursor_to_n(lcmd, *n)) == NULL)
    return (0);
  ntmp = *n - 1;
  while (tmp != NULL && ++ntmp <= max)
    {
      if (tmp->token > PATH && tmp->token != SEMICOLON)
        {
          *n = ntmp;
          return (tmp->token);
        }
      tmp = tmp->next;
    }
  if (tmp == NULL || ntmp >= max)
    {
      ntmp = *n;
      if (get_cmd(lcmd, &ntmp, max) == CMD)
        {
          *n = ntmp;
          return (CMD);
        }
    }
  return (0);
}

t_lcmd  *next_lcmd(t_lcmd *cursor, int retour)
{
  destruct_dlist(&(cursor->cmd));
  cursor = cursor->next;
  while (cursor != NULL)
    {
      if (cursor->tok_beg == AND && retour == 0)
        return (cursor);
      else if (cursor->tok_beg == OR && retour != 0)
        return (cursor);
      else if (cursor->tok_beg == SEMICOLON)
        return (cursor);
      cursor = cursor->next;
    }
  return (cursor);
}

int             nothing_to_do(t_dlist *lcmd, int n, int max)
{
  t_node        *tmp;

  if ((tmp = cursor_to_n(lcmd, n)) == NULL)
    return (1);
  while (tmp != NULL && n <= max)
    {
      if (tmp->token != DA)
        return (-1);
      tmp = tmp->next;
      n += 1;
    }
  return (1);
}
