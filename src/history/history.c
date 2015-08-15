/*
** history.c for  in /home/therou-g/rendu/Unix/PSU_2014_42sh
**
** Made by Gaetan THEROU
** Login   <therou-g@epitech.net>
**
** Started on  Wed May  6 20:01:36 2015 Gaetan THEROU
** Last update Fri May 22 23:24:09 2015 Loic Robin
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <history.h>
#include <get_next_line.h>

void			init_history(t_caps *caps)
{
  int			fd;
  char			*str;
  char			*path;
  struct passwd	*pwd;

  caps->hist = NULL;
  pwd = getpwuid(getuid());
  if (!(path = malloc(strlen(pwd->pw_dir) + strlen(HIST_FILE) + 2)))
    return ;
  bzero(path, strlen(pwd->pw_dir) + strlen(HIST_FILE) + 2);
  path = strcat(path, pwd->pw_dir);
  path = strcat(path, "/");
  path = strcat(path, HIST_FILE);
  if ((fd = open(path, O_RDONLY)) < 0)
    return ;
  caps->hist = crea_list(get_next_line(fd));
  while ((str = get_next_line(fd)))
    {
      add_in_list(caps->hist, str);
      free(str);
    }
  close(fd);
}

t_history		*add_history(t_history *hist, char *cmd)
{
  char			*s;

  s = strndup(cmd, strlen(cmd) - 1);
  if (hist == NULL)
    hist = crea_list(s);
  else
    add_in_list(hist, s);
  free(s);
  return (hist);
}

void			write_history(t_history *list)
{
  int			i;
  int			fd;
  char			*path;
  struct passwd	*pwd;

  i = -1;
  pwd = getpwuid(getuid());
  if (!(path = malloc(strlen(pwd->pw_dir) + strlen(HIST_FILE) + 2)))
    return ;
  bzero(path, strlen(pwd->pw_dir) + strlen(HIST_FILE) + 2);
  path = strcat(path, pwd->pw_dir);
  path = strcat(path, "/");
  path = strcat(path, HIST_FILE);
  if ((fd = open(path, O_CREAT | O_RDWR | O_TRUNC,
		 S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
    return ;
  end(&list);
  while ((list->prev != NULL) && (++i < LEN_HIST))
    list = list->prev;
  while (list != NULL)
    {
      write(fd, list->cmd, strlen(list->cmd));
      write(fd, "\n", 1);
      list = list->next;
    }
}
