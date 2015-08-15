/*
** init.c for  in /home/robin_l/Divers/42OOK
** 
** Made by Loic Robin
** Login   <robin_l@epitech.net>
** 
** Started on  Fri May 22 22:00:05 2015 Loic Robin
** Last update Sat May 23 23:16:32 2015 Loic Robin
*/

#include <signal.h>
#include <unistd.h>
#include "sh.h"

void    newl()
{
  my_fdputstr("\n(42SH)> ", 0);
  nll = 1;
}

void    init_sig()
{
  signal(SIGSEGV, SIG_DFL);
  signal(SIGINT, newl);
  signal(SIGQUIT, SIG_IGN);
}

t_shell *init_shell(t_shell *sh)
{
  sh->lenv = NULL;
  sh->env = NULL;
  sh->retour = 0;
  sh->quit = 0;
  sh->fdout = 1;
  return (sh);
}

t_cmd   *init_cmd(t_cmd *cmd)
{
  cmd->type = 0;
  cmd->retour = 0;
  cmd->lenv = NULL;
  cmd->path = NULL;
  cmd->env = NULL;
  cmd->quit = 0;
  cmd->fdout = 1;
  cmd->fdrchev = 0;
  cmd->fdlchev = 0;
  cmd->ok = 0;
  return (cmd);
}

void    init_exec(t_exec *exec, t_shell *sh)
{
  exec->cmd = NULL;
  exec->pid = 1;
  exec->status = sh->retour;
  exec->token = DA;
  exec->pipe = 0;
  exec->npipe = 0;
  exec->endpipe = 0;
  exec->fd[0] = 0;
  exec->fd[1] = 0;
  exec->lchev = 0;
  exec->rchev = 0;
  exec->fdin = 0;
  exec->fdout = sh->fdout;
}
