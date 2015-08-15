/*
** cd.c for  in /home/robin_l/Divers/MiniShell/MAIN/cd
** 
** Made by Loic Robin
** Login   <robin_l@epitech.net>
** 
** Started on  Sun Jan 25 20:44:57 2015 Loic Robin
** Last update Sat May 23 20:35:08 2015 Loic Robin
*/

#include <unistd.h>
#include "sh.h"

void	error_cd(char **tabx, char *home, t_cmd *cmd)
{
  char	*path;

  cmd->retour = 1;
  if (size_wordtab(tabx) > 1)
    path = tabx[1];
  else
    path = home;
  if (access(path, F_OK) == 0)
    {
      my_fdputstr("bash: cd: ", cmd->fdout);
      my_fdputstr(path, cmd->fdout);
      my_fdputstr("/: Permission denied ", cmd->fdout);
      my_fdputchar('\n', cmd->fdout);
    }
  else
    {
      my_fdputstr("bash: cd: ", cmd->fdout);
      my_fdputstr(path, cmd->fdout);
      my_fdputstr(": No such file or directory", cmd->fdout);
      my_fdputchar('\n', cmd->fdout);
    }
}

t_cmd	*cd_oldpwd(t_cmd *cmd)
{
  char	*opwd;

  if ((opwd = get_info("OLDPWD", cmd->lenv)) == NULL)
    {
      my_fdputstr("bash: cd: OLDPWD not set\n", cmd->fdout);
      cmd->retour = 1;
      return (cmd);
    }
  if ((chdir(opwd)) < 0)
    error_cd(cmd->tabx, opwd, cmd);
  else
    {
      my_fdputstr(opwd, 1);
      my_fdputstr("\n", 1);
    }
  return (cmd);
}

void	set_oldpwd(t_cmd *cmd, char *buffer)
{
  char	*str;

  str = NULL;
  if ((str = strcatrealloc(str, "OLDPWD=", 7)) == NULL)
    return ;
  if ((str = strcatrealloc(str, buffer, my_strlen(buffer))) == NULL)
    return ;
  if (str[my_strlen(str)] != '/')
    if ((str = strcatrealloc(str, "/", 1)) == NULL)
      return ;
  cmd->lenv = mod_info_env("OLDPWD", str, cmd->lenv);
}

void	set_buffer(char buffer[8192], int *ok, t_cmd *cmd)
{
  int	init;

  init = 0;
  while (init < 8192)
    {
      buffer[init] = '\0';
      init += 1;
    }
  getcwd(buffer, 8192);
  *ok = 0;
  cmd->retour = 0;
}

t_cmd	*cd(t_cmd  *cmd)
{
  char	*home;
  char  buffer[8192];
  int	ok;

  set_buffer(buffer, &ok, cmd);
  if ((size_wordtab(cmd->tabx)) > 1)
    if ((my_strcmp(cmd->tabx[1], "-")) == 0)
      cmd = cd_oldpwd(cmd);
    else
      ok = chdir(cmd->tabx[1]);
  else
    {
      if ((home = get_info("HOME", cmd->lenv)) == NULL)
	{
	  cmd->retour = 1;
	  my_fdputstr("bash: cd: HOME not set\n", cmd->fdout);
	  return (cmd);
	}
      ok = chdir(home);
    }
  if (ok < 0)
    error_cd(cmd->tabx, home, cmd);
  else if (ok >= 0 && cmd->retour == 0)
    set_oldpwd(cmd, buffer);
  return (cmd);
}
