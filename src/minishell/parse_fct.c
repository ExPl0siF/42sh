/*
** parse_fct.c for  in /home/robin_l/Divers/42OOK
** 
** Made by Loic Robin
** Login   <robin_l@epitech.net>
** 
** Started on  Fri May 22 22:20:01 2015 Loic Robin
** Last update Fri May 22 22:20:34 2015 Loic Robin
*/

#include "sh.h"

int	check_next_pipe(t_dlist *lcmd, int n, int max)
{
  if ((next_operator(lcmd, &n, max)) == PIPE)
    return (1);
  return (0);
}

t_exec  *close_all(t_exec *exec)
{
  if (exec->fd[1] != 0)
    close(exec->fd[1]);
  if (exec->fd[0] != 0)
    close(exec->fd[0]);
  exec->fd[0] = 0;
  exec->fd[1] = 0;
  return (exec);
}
