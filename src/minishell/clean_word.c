/*
** clean_word.c for  in /home/robin_l/Divers/42OOK
** 
** Made by Loic Robin
** Login   <robin_l@epitech.net>
** 
** Started on  Fri May 22 21:41:25 2015 Loic Robin
** Last update Fri May 22 21:42:31 2015 Loic Robin
*/

#include <unistd.h>
#include "my.h"

void    clean_word_setsplp(char *str, char *s, int *p, int *lp)
{
  *s = 0;
  *lp = *p;
  while (str[*p] != '\0' && is_delim(str[*p], " \t") == 1)
    *p += 1;
  if (*lp != *p)
    *s = 1;
  *lp = *p;
  while (str[*p] != '\0' && is_delim(str[*p], " \t") == 0)
    *p += 1;
}

char    *clean_word(char *str)
{
  char  *clean;
  int   lp;
  int   p;
  char  space;

  clean = NULL;
  p = -1;
  while (is_delim(str[++p], " \t") == 1);
  while (str[p] != '\0')
    {
      clean_word_setsplp(str, &space, &p, &lp);
      if (lp != p)
        {
          if (space == 1)
            if ((clean = strcatrealloc(clean, " ", 1)) == NULL)
              return (NULL);
          if ((clean = strcatrealloc(clean, &str[lp], (p - lp))) == NULL)
            return (NULL);
        }
    }
  return (clean);
}
