/*
** get_next_line.c for  in /home/robin_l/Divers/GetNextLine
**
** Made by Loic Robin
** Login   <robin_l@epitech.net>
**
** Started on  Mon Nov 17 15:19:37 2014 Loic Robin
** Last update Tue May 12 16:35:43 2015 Gaetan THEROU
*/

#include <stdlib.h>
#include <unistd.h>
#include <my.h>
#include <get_next_line.h>

int	set_posn(char *str, int from, int size)
{
  int	i;

  i = from;
  if (str == NULL)
    return (-1);
  while (str[i] != '\0' && i < size)
    {
      if (str[i] == '\n')
	return (i);
      i = i + 1;
    }
  if (str[i] == '\0')
    return (i);
  return (0);
}

int	have_backn(char *str)
{
  int	pos;

  pos = 0;
  if (str == NULL)
    return (0);
  while (str[pos] != '\0')
    {
      if (str[pos] == '\n')
	{
	  str[pos] = '\0';
	  return (1);
	}
      pos = pos + 1;
    }
  return (0);
}

void	init_buffer(char buffer[SIZE], int size, int *posn)
{
  int	pos;

  pos = 0;
  while (pos <= size)
    {
      buffer[pos] = '\0';
      pos = pos + 1;
    }
  buffer[SIZE + 1] = '\0';
  *posn = 0;
}

char		*get_next_line(const int fd)
{
  static char  	buf[SIZE];
  char		*fb;
  static int	pn;
  static int	size;
  int		lpn;

  fb = NULL;
  while (have_backn(fb) <= 0)
    {
      if (pn >= size || pn == 0)
	{
	  init_buffer(buf, SIZE, &pn);
	  if (read(fd, buf, SIZE) <= 0)
	    return (fb);
	  size = my_strlen(buf);
	}
      lpn = pn;
      pn = set_posn(buf, lpn, size);
      if ((fb = strcatrealloc(fb, &buf[lpn], ((pn - lpn) + 1))) == NULL)
	return (NULL);
    }
  pn += 1;
  return (fb);
}
