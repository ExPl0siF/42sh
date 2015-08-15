/*
** auto.c for 42sh in /home/therou-g/rendu/Unix/PSU_2014_42sh
**
** Made by Gaetan THEROU
** Login   <therou-g@epitech.net>
**
** Started on  Wed May 13 23:00:38 2015 Gaetan THEROU
** Last update Fri May 22 15:25:18 2015 Gaetan THEROU
*/

#include <history.h>
#include <dtab.h>
#include <stdlib.h>

void	start_tab(t_tab **list)
{
  if ((*list) == NULL)
    return ;
  while ((*list)->prev != NULL)
    (*list) = (*list)->prev;
}

char	*cpl_command(t_caps *caps, char *src)
{
  int	i;
  char	*str;

  i = caps->cursor_pos;
  if ((str = malloc(my_strlen(src) + my_strlen(caps->cmd) + 1)) == NULL)
    return (NULL);
  while (caps->cmd[i] != ' ' && caps->cmd[i] != '|' && caps->cmd[i] != ';'
	 && caps->cmd[i] != '>' && caps->cmd[i] != '&' && caps->cmd[i] != '<'
	 && caps->cmd[i] != '[' && caps->cmd[i] != ']' && caps->cmd[i] != '/'
	 && i >= 0)
    i--;
  if (i != caps->cursor_pos)
    i += 1;
  else
    i -= 1;
  str = my_strncpy(str, caps->cmd, i);
  str = my_strcat(str, src);
  str = my_strcat(str, caps->cmd + caps->cursor_pos);
  str[my_strlen(str)] = '\0';
  return (str);
}

int	find_max_size(t_lol *cpl)
{
  int	i;
  t_tab	*list;

  list = cpl->list;
  i = 0;
  while (list != NULL)
    {
      if (my_strlen(list->cmd) > i)
	i = my_strlen(list->cmd) + 1;
      list = list->next;
    }
  return (i);
}

int	check_posi(t_caps *caps, t_lol *cpl)
{
  int	i;
  int	max_size;
  char	*buff;
  char	*str;
  char	c;

  buff = save_buff(caps->cmd, caps->cursor_pos);
  max_size = find_max_size(cpl);
  if ((str = malloc(sizeof(char) * max_size + 1)) == NULL)
    return (-1);
  i = my_strlen(buff);
  str = my_strncpy(str, buff, i);
  while ((c = find_next_char(my_strlen_buff(str), cpl)) != 0)
    {
      str[i] = c;
      i++;
    }
  str[i] = '\0';
  caps->save_cmd = my_strdup(str);
  if (my_strcmp(str, buff) == 0)
    return (0);
  return (i);
}

void	exec_auto(t_caps *caps, t_lol *cpl)
{
  if (cpl->nb_item == 1)
    {
      caps->cmd = my_strdup(cpl_command(caps, cpl->list->cmd));
      caps->cursor_pos = my_strlen(caps->cmd);
      aff_cmd(caps);
    }
  else if (cpl->nb_item >= 2)
    {
      start_tab(&cpl->list);
      if (check_posi(caps, cpl) > 0)
	{
	  caps->cmd = my_strdup(cpl_command(caps, caps->save_cmd));
	  caps->cursor_pos = my_strlen(caps->cmd);
	  aff_cmd(caps);
	}
      else
	multi_posi(cpl);
      aff_cmd(caps);
    }
}
