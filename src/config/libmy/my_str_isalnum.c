/*
** my_str_isalnum.c for string in /home/closingin/Documents/Epitech/My/string
**
** Made by      Rémi WEISLINGER
** Login        weisli_r
**
** Started on   Wed Dec 03 17:31:32 2014 weisli_r
** Update       May 23 11:17 2015 closingin
*/

int		my_str_isalnum(char *s)
{
  int	i;

  i = -1;
  while (s && s[++i])
    if (i == 0 && \
        (s[i] < 'A' || s[i] > 'Z') && \
        (s[i] < 'a' || s[i] > 'a'))
      return (0);
    else if (i != 0 && \
        (s[i] < 'A' || s[i] > 'Z') && \
        (s[i] < 'a' || s[i] > 'z') && \
        (s[i] < '0' || s[i] > '9') && \
         s[i] != '_')
      return (0);
  return (1);
}

#include <stdio.h>

int		my_str_isalnum_alias(char *s)
{
  int	i;

  i = -1;
  while (s && s[++i])
    if (!i && \
        (s[i] < 'A' || s[i] > 'Z') && \
        (s[i] < 'a' || s[i] > 'z'))
    {
      return (0);
    }
    else if (i != 0 && \
        (s[i] < 'A' || s[i] > 'Z') && \
        (s[i] < 'a' || s[i] > 'z') && \
        (s[i] < '0' || s[i] > '9') && \
         s[i] != '_' && s[i] != '-')
      return (0);
  return (1);
}
