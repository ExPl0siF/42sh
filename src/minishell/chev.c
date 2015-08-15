/*
** pars_list2.c for  in /home/robin_l/Divers/MiniShell/MYSHV2/MAIN
** 
** Made by Loic Robin
** Login   <robin_l@epitech.net>
** 
** Started on  Wed Feb 25 22:08:23 2015 Loic Robin
** Last update Fri May 22 19:54:40 2015 Loic Robin
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "list.h"
#include "pars.h"
#include "sh.h"
#include "get_next_line.h"

t_exec	*rchev_exec(t_exec *exec, t_dlist *lcmd, int n)
{
  char 	*out;

  out = NULL;
  if ((out = get_out(lcmd, n)) == NULL)
    return (exec);
  out = clean_str(out, " ");
  if ((exec->fdrchev = open(out, O_WRONLY | O_TRUNC | O_CREAT, \
                        S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)) < 0)
    {
      error_open(out, exec->fdout);
      return (exec);
    }
  free(out);
  return (exec);
}

t_exec *rdchev_exec(t_exec *exec, t_dlist *lcmd, int n)
{
  char  *out;

  out = NULL;
  if ((out = get_out(lcmd, n)) == NULL)
    return (exec);
  out = clean_str(out, " ");
  if ((exec->fdrchev = open(out, O_WRONLY | O_CREAT | O_APPEND, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)) < 0)
    {
      error_open(out, exec->fdout);
      return (exec);
    }
  free(out);
  return (exec);
}

t_exec	*lchev_exec(t_exec *exec, t_dlist *lcmd, int n, int *fdin)
{
  char  *in;

  in = NULL;
  if ((in = get_out(lcmd, n)) == NULL)
    {
      my_fdputstr("Erreur aucune entrée trouvé\n", 2);
      return (exec);
    }
  in = clean_str(in, " ");
  if ((*fdin = open(in, O_RDONLY, \
			  S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)) < 0)
    error_open(in, exec->fdout);
  free(in);
  return (exec);
}

t_exec	*ldchev_getin(t_exec *exec, char *in, int tmpfd[2], int pid)
{
  char	*tmp;

  if ((pid = fork()) < 0)
    return (exec);
  if (pid == 0)
    {
      signal(SIGINT, SIG_DFL);
      close(tmpfd[0]);
      while ((my_putstr(">")) == 0 && (tmp = get_next_line(0)))
	{
	  if ((my_strcmp(in, tmp)) == 0)
	    exit(EXIT_SUCCESS);
	  my_fdputstr(tmp, tmpfd[1]);
	  my_fdputstr("\n", tmpfd[1]);
	  free(tmp);
	}
    }
  else
    {
      close(tmpfd[1]);
      exec->tmp = tmpfd[0];
      waitpid(pid, 0, 0);
    }
  return (exec);
}

t_exec	*ldchev_exec(t_exec *exec, t_dlist *lcmd, int n, int *fdin)
{
  int	tmpfd[2];
  int	pid;
  char  *in;

  in = NULL;
  pid = 0;
  if ((in = get_out(lcmd, n)) == NULL)
    return (exec);
  in = clean_str(in, " ");
  if ((pipe(tmpfd)) <  0)
    return (exec);
  exec = ldchev_getin(exec, in, tmpfd, pid);
  *fdin = exec->tmp;
  free(in);
  return (exec);
}
