/*
** pars_list3.c for  in /home/robin_l/Divers/MiniShell/MYSHV2/MAIN
** 
** Made by Loic Robin
** Login   <robin_l@epitech.net>
** 
** Started on  Sun Mar  8 15:01:39 2015 Loic Robin
** Last update Sat May 23 18:04:07 2015 Loic Robin
*/

#include <stdlib.h>
#include <unistd.h>
#include "pars.h"
#include "sh.h"

int	set_stop_max_and_out(int redir, int token, int stop)
{
  if (stop == 1)
    return (1);
  if (redir == 1 && (token == PIPE))
    return (1);
  else
    return (0);
}

int             get_n_lchev(t_dlist *lcmd, int n)
{
  t_node        *tmp;

  if ((tmp = cursor_to_n(lcmd, n)) == NULL)
    return (-1);
  while (tmp != NULL)
    {
      if (tmp->token == CMD || tmp->token == BUILTIN)
        return (n);
      tmp = tmp->prev;
      n -= 1;
    }
  return (0);
}

t_node	*set_redir_in(t_node *in, int fdin, int *redir)
{
  in->token = INGO;
  in->fd = fdin;
  *redir = 0;
  return (in);
}

t_exec         *set_in(t_exec *exec, t_dlist *lcmd, int n)
{
  t_node        *tmp;
  t_node	*in;
  int		redir;
  int		fdin;

  n = 0;
  redir = 0;
  tmp = lcmd->first;
  fdin = 0;
  while (tmp != NULL)
    {
      if (tmp->token == LCHEV || tmp->token == LDCHEV)
	{
	  if (tmp->token == LCHEV)
	    exec = lchev_exec(exec, lcmd, n, &fdin);
	  if (tmp->token == LDCHEV)
	    exec = ldchev_exec(exec, lcmd, n, &fdin);
	  in = set_in_and_redir(in, tmp, &redir);
	}
      n += 1;
      if (redir == 1 && (tmp->token == PIPE || tmp->next == NULL))
	in = set_redir_in(in, fdin, &redir);
      tmp = tmp->next;
    }
  return (exec);
}

int		get_fdin(t_dlist *lcmd, int n)
{
  t_node        *tmp;

  if ((tmp = cursor_to_n(lcmd, n)) == NULL)
    return (-1);
  tmp->token = DA;
  return (tmp->fd);
}
