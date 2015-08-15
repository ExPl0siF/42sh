/*
** process_builtin.c for  in /home/robin_l/Divers/42SH
** 
** Made by Loic Robin
** Login   <robin_l@epitech.net>
** 
** Started on  Tue May 19 22:50:26 2015 Loic Robin
** Last update Sat May 23 18:14:50 2015 Loic Robin
*/

#include "pars.h"
#include "sh.h"

t_exec	*exec_builtin(t_exec *exec)
{
  int	l;

  l = 0;
  if (exec->cmd == NULL)
    return (exec);
  if (exec->cmd->tabx == NULL || exec->cmd->tabx[0] == NULL)
    return (exec);
  while (l < NB_BUILTIN)
    {
      if ((my_strcmp(exec->cmd->tabx[0], lbuiltin[l].str)) == 0)
	lbuiltin[l].fct(exec->cmd);
      l += 1;
    }
  return (exec);
}
