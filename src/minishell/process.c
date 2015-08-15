/*
** process.c for  in /home/robin_l/Divers/MiniShell/MYSHV2/MAIN
** 
** Made by Loic Robin
** Login   <robin_l@epitech.net>
** 
** Started on  Mon Feb 23 21:16:53 2015 Loic Robin
** Last update Sat May 23 15:31:21 2015 Loic Robin
*/

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include "sh.h"

void	kill_myself()
{
  pid_t	pid;

  pid = getpid();
  kill(pid, SIGTERM);
}

t_exec *check_case_child(t_exec *exec)
{
  signal(SIGINT, SIG_DFL);
  if (exec->pipe == 1)
    {
      close(exec->fd[0]);
      exec->fd[0] = 0;
    }
  if (exec->lchev == 1 || exec->pipe == 1)
    dup2(exec->fdin, 0);
  if (exec->npipe == 1 && exec->pipe == 1)
    dup2(exec->fd[1], 1);
  if (exec->rchev == 1)
    dup2(exec->fdout, 1);
  built_or_exec(exec);
  kill_myself();
  return (exec);
}

t_exec	*check_case_dad(t_exec *exec)
{
  if (exec->lchev == 1)
    {
      close(exec->fdin);
      exec->lchev = 0;
    }
  if (exec->pipe == 1)
    {
      close(exec->fd[1]);
      exec->fd[1] = 0;
      exec->fdin = exec->fd[0];
    }
  if (exec->rchev == 1)
    {
      if (close(exec->fdout) < 0)
	return (exec);
      exec->rchev = 0;
      exec->fdout = 0;
    }
  return (exec);
}

t_exec	*process(t_exec *exec)
{
  if (exec->pipe == 0 && exec->cmd->type == BUILTIN && exec->rchev == 0)
    return (exec_builtin(exec));
  if (exec->pipe == 1)
    if ((pipe_it(exec)) < 0)
      return (exec);
  if ((fork_it(exec)) < 0)
    return (exec);
  if (exec->pid == 0)
    exec = check_case_child(exec);
  else
    {
      inhib_signal();
      exec = check_case_dad(exec);
      if (exec->pipe == 1)
	{
	  if (exec->endpipe == 0)
	    waitpid(exec->pid, &(exec->status), WNOHANG);
	  else
	    waitpid(exec->pid, &(exec->status), WCONTINUED);
	}
      else
	waitpid(exec->pid, &(exec->status), WCONTINUED);
    }
  init_sig();
  return (exec);
}
