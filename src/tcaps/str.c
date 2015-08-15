/*
** str.c for 42sh in /home/therou-g/rendu/Unix/PSU_2014_42sh
**
** Made by Gaetan THEROU
** Login   <therou-g@epitech.net>
**
** Started on  Tue May 12 15:55:26 2015 Gaetan THEROU
** Last update Sun May 24 17:17:20 2015 Loic Robin
*/

#include <stdlib.h>
#include <history.h>
#include <my.h>

char    *put_char_str(char *src, char c, int pos)
{
  char  *str;

  str = NULL;
  str = strcatrealloc(str, src, pos);
  str = strcatrealloc(str, &c, 1);
  str = strcatrealloc(str, &(src[pos]), (my_strlen(src) - pos));
  return (str);
}

char	*my_delete_char(t_caps *caps)
{
  int   s;
  int	pos;
  char	*str;

  s = 0;
  pos = caps->cursor_pos;
  s = my_strlen(caps->cmd);
  str = NULL;
  str = strcatrealloc(str, caps->cmd, (pos - 1));
  str = strcatrealloc(str, &(caps->cmd[pos]), (s - pos));
  caps->cursor_pos -= 1;
  return (str);
}
