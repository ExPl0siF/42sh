/*
** error_aff.c for  in /home/robin_l/Divers/42OOK
** 
** Made by Loic Robin
** Login   <robin_l@epitech.net>
** 
** Started on  Fri May 22 22:03:27 2015 Loic Robin
** Last update Fri May 22 22:04:00 2015 Loic Robin
*/

#include "sh.h"

void    error_open(char *path, int fd)
{
  my_fdputstr("bash: ", fd);
  my_fdputstr(path, fd);
  my_fdputstr(": No such file or directory", fd);
  my_fdputstr("\n", fd);
}

void    error_cmd(char *cmd, int fd, int type)
{
  if (type != -2)
    {
      my_fdputstr(cmd, fd);
      my_fdputstr(": command not found", fd);
      my_fdputchar('\n', fd);
    }
  else if (type == -2)
    error_open(cmd, 2);
}
