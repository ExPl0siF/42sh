/*
** shell_process.c for  in /home/robin_l/Divers/MiniShell/MAIN
** 
** Made by Loic Robin
** Login   <robin_l@epitech.net>
** 
** Started on  Mon Jan 26 21:02:01 2015 Loic Robin
** Last update Sat May 23 23:03:04 2015 Loic Robin
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include "sh.h"

t_cmd	*my_echo(t_cmd *cmd)
{
  if (cmd->tabx != NULL)
  {
    if (size_wordtab(cmd->tabx) > 1)
      my_echo_one(cmd);
    else
      my_fdputchar('\n', 1);
  }
  cmd->retour = 0;
  return (cmd);
}

t_cmd	*leave(t_cmd *cmd)
{
  cmd->retour = 0;
  if (cmd->tabx != NULL)
    {
      if (size_wordtab(cmd->tabx) > 1)
	{
	  cmd->retour = my_getnbr(cmd->tabx[1]);
	}
    }
  cmd->quit = 1;
  return (cmd);
}

t_cmd	*my_setenv_noarg(t_cmd *cmd)
{
  char  *s;

  s = NULL;
  if ((s = strcatrealloc(s, cmd->tabx[1], (my_strlen(cmd->tabx[1])))) == NULL)
    return (cmd);
  if ((s = strcatrealloc(s, "=", 1)) == NULL)
    return (cmd);
  if ((get_nbnode_info(cmd->tabx[1], cmd->lenv)) > 0)
    cmd->lenv = mod_info_env(cmd->tabx[1], s, cmd->lenv);
  else
    cmd->lenv = push_end(cmd->lenv, s, 0);
  cmd->env = list_in_env(cmd->env, cmd->lenv);
  if (s != NULL)
    free(s);
  cmd->retour = 0;
  return (cmd);
}

t_cmd	*setenv_badargs(t_cmd *cmd)
{
  my_fdputstr("setenv [NAME] [VALUE]\n", cmd->fdout);
  cmd->retour = 1;
  return (cmd);
}

t_cmd	*my_setenv(t_cmd *c)
{
  char  *s;

  s = NULL;
  if (size_wordtab(c->tabx) < 2)
    c = setenv_badargs(c);
  else if (size_wordtab(c->tabx) == 2)
    c = my_setenv_noarg(c);
  else if (size_wordtab(c->tabx) == 3)
    {
      if ((s = strcatrealloc(s, c->tabx[1], (my_strlen(c->tabx[1])))) == NULL)
        return (c);
      if ((s = strcatrealloc(s, "=", 1)) == NULL)
        return (c);
      if ((s = strcatrealloc(s, c->tabx[2], (my_strlen(c->tabx[2])))) == NULL)
        return (c);
      if ((get_nbnode_info(c->tabx[1], c->lenv)) > 0)
        c->lenv = mod_info_env(c->tabx[1], s, c->lenv);
      else
        c->lenv = push_end(c->lenv, s, 0);
      c->env = list_in_env(c->env, c->lenv);
      if (s != NULL)
        free(s);
      c->retour = 0;
    }
  return (c);
}
