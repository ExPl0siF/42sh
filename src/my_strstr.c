/*
** my_strstr.c for  in /home/casell_t/rendu/Piscine_C_J06
**
** Made by Theo Caselli
** Login   <casell_t@epitech.net>
**
** Started on  Mon Oct  6 11:05:49 2014 Theo Caselli
** Last update Wed May 13 16:10:45 2015 Theo Caselli
*/

#include <stdlib.h>
#include "my.h"

int	my_strstrint(char *str, char *to_find)
{
  int	a;
  int	b;

  a = 0;
  b = 0;
  if (to_find == NULL)
    return (-1);
  while (str[a] != '\0')
    {
      if (str[a] == to_find[b])
	{
	  while ((str[a] == to_find[b]) && (to_find[b] != '\0' || str[a] != '\0'))
	    {
	      a++;
	      b++;
	    }
	  return ((to_find[b] == 0) ? 1 : 0);
	}
      a++;
    }
  return (0);
}
