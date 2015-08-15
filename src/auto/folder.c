/*
** main.c for  in /home/ExPl0siF/Bin/base_directory
**
** Made by Theo Caselli
** Login   <casell_t@epitech.net>
**
** Started on  Wed May  6 13:34:46 2015 Theo Caselli
** Last update Fri May 22 02:33:02 2015 Theo Caselli
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <termios.h>
#include <ncurses.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <term.h>
#include <history.h>
#include <dtab.h>
#include <my.h>

DIR	*chefol(char *buff, int i)
{
  int	j;
  DIR	*dir;
  char	*tmp_two;

  j = -1;
  tmp_two = NULL;
  if (i != 0)
    {
      if ((tmp_two = malloc(my_strlen(buff))) == NULL)
	return (NULL);
      while (++j != i)
	tmp_two[j] = buff[j];
      tmp_two[j] = 0;
    }
  else
    tmp_two = strcatrealloc(tmp_two, buff, my_strlen(buff));
  dir = opendir(tmp_two);
  return (dir);
}

DIR	*open_direct(char *buff, int i, DIR *dir)
{
  int	j;
  char	*tmp;

  j = -1;
  if ((tmp = malloc(my_strlen(buff) + 2)) == NULL)
    return (NULL);
  if (i != 0)
    {
      while (++j != i - 1)
	tmp[j] = buff[j];
      tmp[j] = 0;
    }
  else
    tmp = my_strcpy(tmp, buff);
  if (my_strstrint(buff, "/") == 1 && buff[0] != '.' && buff[0] != '/')
    dir = opendir(tmp);
  else
    dir = (buff[0] == '.' || buff[0] == '/') ? (chefol(buff, i)) : opendir(".");
  return (dir);
}

int	check_fold(char *cmd, char *buff)
{
  int	i;
  int	fd;
  char	*tmp;

  i = my_strlen(buff);
  fd = 0;
  tmp = NULL;
  if (my_strstrint(buff, "/") == 1)
    {
      tmp = strcatrealloc(tmp, buff, my_strlen(buff));
      while (tmp[--i] != '/')
	tmp[i] = 0;
    }
  tmp = strcatrealloc(tmp, cmd, my_strlen(cmd));
  if ((fd = open(tmp, O_DIRECTORY)) < 0)
    return (1);
  else
    {
      close(fd);
      return (0);
    }
}
