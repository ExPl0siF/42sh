/*
** process2.c for  in /home/robin_l/Divers/MiniShell/MYSHV2/MAIN
** 
** Made by Loic Robin
** Login   <robin_l@epitech.net>
** 
** Started on  Sun Mar  8 15:26:24 2015 Loic Robin
** Last update Sat May 23 18:13:51 2015 Loic Robin
*/

#include "sh.h"

int	built_or_exec(t_exec *exec)
{
  if (exec->cmd->type == CMD && exec->cmd->ok == 1)
    if ((execve(exec->cmd->path, exec->cmd->tabx, exec->cmd->env)) < 0)
      {
        if (exec->pipe == 0)
          error_cmd(exec->cmd->tabx[0], exec->fdout, 0);
        else
          error_cmd(exec->cmd->tabx[0], exec->fd[1], 0);
      }
  if (exec->cmd->type == BUILTIN)
    exec_builtin(exec);
  if (exec->cmd->ok == -1 && exec->pipe == 1 && exec->endpipe == 1)
    error_cmd(exec->cmd->tabx[0], exec->fdout, exec->cmd->error);
  else if (exec->cmd->ok == -1 && exec->pipe == 1)
    error_cmd(exec->cmd->tabx[0], exec->fd[1], exec->cmd->error);
  else if (exec->cmd->ok == -1 && exec->pipe == 0)
    error_cmd(exec->cmd->tabx[0], exec->fdout, exec->cmd->error);
  return (0);
}

int     pipe_it(t_exec *exec)
{
  if ((pipe(exec->fd)) < 0)
    {
      my_fdputstr("Erreur Pipe\n", 2);
      return (-1);
    }
  return (1);
}

int     fork_it(t_exec *exec)
{
  if ((exec->pid = fork()) < 0)
    {
      my_fdputstr("Erreur Fork\n", 2);
      return (-1);
    }
  return (1);
}
