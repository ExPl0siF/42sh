/*
** my_strndup.c for string in /home/closingin/Documents/Epitech/My/string
**
** Made by      Rémi WEISLINGER
** Login        closingin
**
** Started on   Mar 01 15:14 2015 closingin
** Update       May 23 10:08 2015 closingin
*/

#include <stdlib.h>
#include <strings.h>

char	*my_strndup(char *s, int n)
{
  char	*res;

  if (s)
  {
    if (!(res = malloc(sizeof(char) * (n + 1))))
      return (NULL);
    bzero(res, n + 1);
    return (strncpy(res, s, n));
  }
  return (NULL);
}
