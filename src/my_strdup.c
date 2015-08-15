/*
** my_strdup.c for  in /home/therou_g/Piscine_C_J08/ex_01
**
** Made by gaetan therou
** Login   <therou_g@epitech.net>
**
** Started on  Wed Oct  8 08:49:30 2014 gaetan therou
** Last update Sun Mar  8 14:27:48 2015 Gaetan THEROU
*/

#include <stdlib.h>
#include "my.h"

char	*my_strdup(char *src)
{
  int	size;
  char	*cpy;

  size = my_strlen(src);
  if ((cpy = malloc(sizeof(char) * size + 1)) == NULL)
    return (NULL);
  my_strcpy(cpy, src);
  return (cpy);
}
