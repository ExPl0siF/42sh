/*
** parse.c for  in /home/robin_l/Divers/42SH
** 
** Made by Loic Robin
** Login   <robin_l@epitech.net>
** 
** Started on  Mon May 11 19:40:31 2015 Loic Robin
** Last update Sat May 23 18:12:33 2015 Loic Robin
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include "pars.h"
#include "my.h"

t_exec	*end_exec_it(t_exec *exec, t_cmd *cmd, t_shell *sh)
{
  process(exec);
  sh->lenv = cmd->lenv;
 if (exec->pipe == 0)
    sh->quit = cmd->quit;
  if (cmd->type == BUILTIN)
    exec->status = cmd->retour;
  if (exec->endpipe == 1)
    {
      close_all(exec);
      exec->endpipe = 0;
    }
  clean_wordtab(cmd->env);
  clean_wordtab(cmd->tabx);
  return (exec);
}

t_exec         *exec_it(t_dlist *lcmd, t_exec *exec, int n, t_shell *sh)
{
  t_cmd		cmd;

  init_cmd(&cmd);
  cmd.lenv = sh->lenv;
  cmd.retour = exec->status;
  if ((cmd.env = list_in_env(cmd.env, sh->lenv)) == NULL)
    return (exec);
  exec->endpipe = 0;
  if ((exec->token == BUILTIN || exec->token == CMD) && exec->pipe == 1)
    {
      exec->endpipe = 1;
      if (exec->rchev == 0)
	exec->fdout = 1;
    }
  load_command_tab(&cmd, lcmd, n);
  if ((size_wordtab(cmd.tabx)) < 1)
    return (exec);
  exec->cmd = &cmd;
  if (exec->lchev == 1 && exec->fdin < 0)
   {
     exec->lchev = 0;
     return (exec);
   }
  end_exec_it(exec, &cmd, sh);
  return (exec);
}

t_exec	*check_outin_go(t_exec *exec, t_dlist *lcmd, int n)
{
  t_node	*tmp;

  tmp = NULL;
  if (exec->token == OUTGO)
    {
      if ((tmp = cursor_to_n(lcmd, n)) == NULL)
	return (exec);
      tmp->token = DA;
      exec->rchev = 1;
      exec->fdout = exec->fdrchev;
    }
  if (exec->token == INGO)
    {
      exec->lchev = 1;
      exec->fdin = get_fdin(lcmd, n);
    }
  return (exec);
}

int		under_pars_cmd(t_lcmd *lcmd, t_shell *sh)
{
  int		n;
  int		max;
  t_exec	exec;

  init_exec(&exec, sh);
  max = lcmd->cmd->length;
  set_in(&exec, lcmd->cmd, 0);
  set_max_and_out(&exec, lcmd->cmd, 0, &max);
  init_exec(&exec, sh);
  while ((nothing_to_do(lcmd->cmd, 0, (lcmd->cmd->length - 1))) != 1)
    {
      n = 0;
      if ((nothing_to_do(lcmd->cmd, n, max)) == 1)
	set_max_and_out(&exec, lcmd->cmd, 0, &max);
      exec.token = next_operator(lcmd->cmd, &n, max);
      if (exec.token == PIPE)
        exec.pipe = 1;
      check_outin_go(&exec, lcmd->cmd, n);
      exec.npipe = check_next_pipe(lcmd->cmd, n, max);
      if (exec.token != INGO && exec.token != OUTGO)
	exec_it(lcmd->cmd, &exec, n, sh);
      sh->retour = exec.status;
    }
  close_all(&exec);
  return (exec.status);
}

int		parse_lcmd(t_lcmd *lcmd, t_shell *sh)
{
  t_lcmd	*cursor;
  int		retour;

  cursor = lcmd;
  retour = 1;
  cursor->cmd = find_path_cmd(cursor->cmd, sh->lenv);
  while (cursor != NULL)
    {
      retour = under_pars_cmd(cursor, sh);
      cursor = next_lcmd(cursor, retour);
      if (cursor != NULL)
	cursor->cmd = find_path_cmd(cursor->cmd, sh->lenv);
    }
  sh->retour = retour;
  return (0);
}
