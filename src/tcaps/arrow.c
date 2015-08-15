/*
** arrow.c for 42sh in /home/therou-g/rendu/Unix/PSU_2014_42sh
**
** Made by Gaetan THEROU
** Login   <therou-g@epitech.net>
**
** Started on  Tue May 12 15:42:58 2015 Gaetan THEROU
** Last update Fri May 15 21:01:13 2015 gaetan therou
*/

#include <termios.h>
#include <curses.h>
#include <term.h>
#include <stdlib.h>
#include <my.h>
#include <history.h>

void	exec_history(t_caps *caps)
{
  if (caps->buff[2] == TOP)
    {
      if (caps->pos_hist < LEN_HIST)
	caps->pos_hist++;
      caps->cmd = find_in_history(caps->hist, caps->pos_hist);
    }
  if (caps->buff[2] == BOT)
    {
      if (caps->pos_hist > 0)
	caps->pos_hist--;
      caps->cmd = find_in_history(caps->hist, caps->pos_hist);
    }
  caps->cursor_pos = my_strlen(caps->cmd);
}

void	exec_cursor(t_caps *caps)
{
  if (caps->buff[2] == LEFT)
    {
      if (caps->cursor_pos > 0)
	{
	  caps->cursor_pos--;
	  tputs(tgoto(tgetstr("le", NULL), 1, 1), 1, my_put_getstr);
	}
    }
  if (caps->buff[2] == RIGHT)
    {
      if (my_strlen(caps->cmd) > caps->cursor_pos)
	{
	  caps->cursor_pos++;
	  tputs(tgoto(tgetstr("nd", NULL), 1, 1), 1, my_put_getstr);
	}
    }
}

void    exec_arrow(t_caps *caps)
{
  if ((caps->buff[2] == TOP) || (caps->buff[2] == BOT))
    exec_history(caps);
  if ((caps->buff[2] == LEFT) || (caps->buff[2] == RIGHT))
    exec_cursor(caps);
  aff_cmd(caps);
}
