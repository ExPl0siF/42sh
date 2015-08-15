/*
** get_caps.c for 42sh in /home/therou-g/rendu/Unix/PSU_2014_42sh
**
** Made by Gaetan THEROU
** Login   <therou-g@epitech.net>
**
** Started on  Tue May 12 15:38:30 2015 Gaetan THEROU
** Last update Sat May 23 19:22:37 2015 Loic Robin
*/

#include <termios.h>
#include <curses.h>
#include <term.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <history.h>
#include <sh.h>

int     raw_mode(t_caps *caps)
{
  if (tcsetattr(0, TCSAFLUSH, &(caps->term)) == -1)
    return (-1);
  return (0);
}

int     is_print_char(char c)
{
  if (c > 31 && c < 127)
    return (1);
  else
    return (0);
}

void	init_tcaps(t_caps *caps, t_dlist *lenv)
{
  caps->cmd = NULL;
  memset(caps->buff, 0, 4);
  caps->pos_hist = 0;
  caps->cursor_pos = 0;
  caps->nb_tab = 0;
  caps->lenv = lenv;
  caps->ok = 1;
}

char	*my_read(t_caps *caps)
{
  if (raw_mode(caps) == -1)
    return (NULL);
  aff_cmd(caps);
  while (caps->buff[0] != '\n' && nll == 0)
  {
    memset(caps->buff, 0, 4);
    if (read(0, caps->buff, 4) <= 0)
      return (NULL);
    if (is_print_char(caps->buff[0]))
      {
	caps->cmd = put_char_str(caps->cmd, caps->buff[0], caps->cursor_pos++);
	aff_cmd(caps);
      }
    else
      buff_read_cmd(caps);
    if (caps->ok == 0)
      return (NULL);
  }
  if ((caps->cmd = strcatrealloc(caps->cmd, "\n", 1)) == NULL)
    return (NULL);
  if (tcsetattr(0, 0, &(caps->save)) == -1)
    return (NULL);
  if (caps->cmd != NULL)
    caps->hist = add_history(caps->hist, caps->cmd);
  return (caps->cmd);
}
