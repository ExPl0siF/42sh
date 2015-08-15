/*
** get_path.c for  in /home/robin_l/Divers/MiniShell/MAIN
** 
** Made by Loic Robin
** Login   <robin_l@epitech.net>
** 
** Started on  Sun Jan 25 18:32:59 2015 Loic Robin
** Last update Fri May 22 02:03:08 2015 Loic Robin
*/

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "my.h"
#include "sh.h"

char	*get_word(char *str, int *start, char *delim, char *word)
{
  int	stop;

  stop = *start;
  if (str == NULL || delim == NULL)
    return (NULL);
  while ((is_delim(str[stop], delim)) == 0 && str[stop] != '\0')
    stop = stop + 1;
  if ((word = strcatrealloc(word, &str[*start], (stop - *start))) == NULL)
    return (NULL);
  if ((word = strcatrealloc(word, "/", 1)) == NULL)
    return (NULL);
  *start = stop + 1;
  return (word);
}

char	*test_path(char *cmd, char *path, int *ok, char *sys_path)
{
  int	s;

  s = 0;
  if ((path = strcatrealloc(path, cmd, my_strlen(cmd))) == NULL)
    return (NULL);
  while ((*ok = access(path, X_OK)) != 0 && sys_path[s] != '\0')
    {
      if (path != NULL)
	free(path);
      path = NULL;
      if ((path = get_word(sys_path, &s, ":", path)) == NULL)
	return (NULL);
      if ((path = strcatrealloc(path, cmd, my_strlen(cmd))) == NULL)
	return (NULL);
    }
  return (path);
}

char	*path_no_path(char *path, char *cmd, int *ok)
{
  if (cmd == NULL)
    return (NULL);
  if (access(cmd, X_OK) == 0)
    {
      if ((path = strcatrealloc(path, cmd, my_strlen(cmd))) == NULL)
	return (NULL);
      *ok = 0;
    }
  return (path);
}

int	str_noslash_and_acsok(char *cmd)
{
  int	i;
  int	slash;
  int	acs;

  i = 0;
  acs = access(cmd, X_OK);
  slash = 0;
  if (cmd == NULL)
    return (1);
  while (cmd[i] != '\0')
    {
      if (cmd[i] == '/')
	slash += 1;
      i += 1;
    }
  if (slash == 0 && acs == 0)
    return (1);
  return (0);
}

char   	*get_path(char *cmd, char *path, int *ispath, t_dlist *lenv)
{
  int	ok;
  char	*sys_path;

  ok = 1;
  path = NULL;
  sys_path = NULL;
  if ((str_noslash_and_acsok(cmd)) == 1)
    return (path);
  if (my_strlen(cmd) >= 2)
    if (cmd[0] == '/' && (access(cmd, X_OK) != 0))
      {
	*ispath = -2;
	return (path);
      }
  if ((sys_path = get_info("PATH", lenv)) == NULL)
    path = path_no_path(path, cmd, &ok);
  else
    path = test_path(cmd, path, &ok, sys_path);
  if (ok == 0)
    *ispath = 1;
  else
    path = strcatrealloc(path, cmd, my_strlen(cmd));
  return (path);
}
