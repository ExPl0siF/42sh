/*
** print_auto.c for 42sh in /home/therou-g/rendu/Unix/PSU_2014_42sh
**
** Made by Gaetan THEROU
** Login   <therou-g@epitech.net>
**
** Started on  Thu May 21 17:23:45 2015 Gaetan THEROU
** Last update Fri May 22 15:24:21 2015 Gaetan THEROU
*/

#include <history.h>
#include <dtab.h>
#include <stdlib.h>

void	print_res(t_lol *cpl, int char_col, int nb_col)
{
  int	b_n;
  int	space;

  b_n = 0;
  my_putchar('\n');
  while (cpl->list != NULL)
    {
      space = -1;
      b_n++;
      my_printf("%s", cpl->list->cmd);
      while ((++space + my_strlen(cpl->list->cmd)) < char_col)
	my_putchar(' ');
      cpl->list = cpl->list->next;
      if (b_n == nb_col)
	{
	  my_putchar('\n');
	  b_n = 0;
	}
    }
  my_putchar('\n');
}

void	multi_posi(t_lol *cpl)
{
  int	max_col;
  int	max;
  int	char_col;
  t_tab	*size;

  start_tab(&cpl->list);
  size = cpl->list;
  max = 0;
  max_col = tgetnum("co");
  while (size != NULL)
    {
      if (my_strlen(size->cmd) > max)
	max = my_strlen(size->cmd) + 1;
      size = size->next;
    }
  char_col = max_col / (max_col / max);
  if ((max_col / max) > cpl->nb_item)
    char_col += 4;
  print_res(cpl, char_col, (max_col / max));
}

char	find_next_char(int i, t_lol *cpl)
{
  char	c;
  t_tab	*list;

  c = 0;
  list = cpl->list;
  start_tab(&list);
  c = list->cmd[i];
  if (list->cmd[i] != '.' && list->cmd[i] != '-')
    while (list != NULL)
      {
	if (list->cmd[i] != c)
	  return (0);
	list = list->next;
      }
  else
    return (0);
  return (c);
}

int	my_strlen_buff(char *str)
{
  int	i;
  int	j;

  i = 0;
  j = 0;
  while (str[i] != '\0')
    {
      if (str[i] != '.' && str[i] != '/')
	j++;
      i++;
    }
  return (j);
}

char	*save_buff(char *src, int pos)
{
  char	*str;

  if ((str = malloc(sizeof(char) * my_strlen(src) + 1)) == NULL)
    return (NULL);
  while ((pos > 0) && src[pos] != ' ' && src[pos] != '|' && src[pos] != ';'
	   && src[pos] != '>' && src[pos] != '&' && src[pos] != '<'
	   && src[pos] != '[' && src[pos] != ']' && src[pos] != '/')
    pos--;
  if (src[pos] == '/')
    pos++;
  str = my_strcpy(str, src + pos);
  return (str);
}
