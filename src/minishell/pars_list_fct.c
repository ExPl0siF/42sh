/*
** pars_list_fct.c for  in /home/robin_l/Divers/MiniShell/MYSHV2/MAIN/parlex
** 
** Made by Loic Robin
** Login   <robin_l@epitech.net>
** 
** Started on  Thu Feb 19 16:03:15 2015 Loic Robin
** Last update Fri May 22 21:19:03 2015 Loic Robin
*/

#include <stdlib.h>
#include <unistd.h>
#include "list.h"
#include "pars.h"
#include "sh.h"

t_exec	*is_redir(t_exec *exec, t_dlist *lcmd, int n, int token)
{
  if (token == RCHEV)
    exec = rchev_exec(exec, lcmd, n);
  if (token == RDCHEV)
    exec = rdchev_exec(exec, lcmd, n);
  return (exec);
}

int   	end_max_and_out(int redir, t_node *tmp, int n, int stop)
{
  int	max;

 if (redir == 1)
   tmp->token = OUTGO;
  max = n;
  if (stop == 1)
    max -= 1;
  return (max);
}

t_exec		*set_max_and_out(t_exec *exec, t_dlist *lcmd, int n, int *max)
{
  int		redir;
  int		stop;
  t_node	*tmp;
  t_node	*lredir;

  redir = 0;
  stop = 0;
  if ((tmp = cursor_to_n(lcmd, n)) == NULL)
    return (exec);
  while (tmp != NULL && stop == 0)
    {
      if (tmp->token == SEMICOLON || tmp->token == 0)
	stop = 1;
      if (tmp->token == RCHEV || tmp->token == RDCHEV)
	{
	  exec = is_redir(exec, lcmd, n, tmp->token);
	  redir = 1;
	  lredir = tmp;
	}
      stop = set_stop_max_and_out(redir, tmp->token, stop);
      tmp = tmp->next;
      n += 1;
    }
  *max = end_max_and_out(redir, lredir, n, stop);
  return (exec);
}
