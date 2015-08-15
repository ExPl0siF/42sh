/*
** my_free_wordtab.c for stdlib in /home/closingin/Documents/Epitech/My/stdlib
**
** Made by      Rémi WEISLINGER
** Login        closingin
**
** Started on   Jan 27 00:46 2015 closingin
** Update       May 23 09:56 2015 closingin
*/

#include <stdlib.h>

int		my_free_wordtab(char **wtab)
{
  int	i;

  i = -1;
  if (wtab)
  {
    while (wtab[++i])
      free(wtab[i]);
    free(wtab[i]);
    free(wtab);
    return (1);
  }
  return (0);
}
