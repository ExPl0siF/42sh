/*
** my_strinit.c for my in /home/closingin/Documents/Epitech/Rendu/Piscine_C_J11/lib/my
**
** Made by      Rémi WEISLINGER
** Login        weisli_r
**
** Started on   Sat Oct 25 20:19:59 2014 weisli_r
** Update       May 18 16:21 2015 closingin
*/

#include <stdlib.h>
#include <string.h>

char	*my_strinit(int length)
{
  char	*str;

  if (!(str = malloc(length)))
    return (NULL);
  return (memset(str, '\0', length));
}
