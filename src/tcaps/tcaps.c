/*
** tcaps.c for 42sh in /home/therou-g/rendu/Unix/PSU_2014_42sh
**
** Made by Gaetan THEROU
** Login   <therou-g@epitech.net>
**
** Started on  Tue May 12 15:44:02 2015 Gaetan THEROU
** Last update Sat May 23 18:16:01 2015 Loic Robin
*/

#include <stdlib.h>
#include <curses.h>
#include <sys/types.h>
#include <pwd.h>
#include <term.h>
#include <unistd.h>
#include <history.h>
#include <dtab.h>
#include <list.h>
#include <my.h>
#include <sh.h>

int				my_put_getstr(int c)
{
  write(0, &c, 1);
  return (0);
}

void			buff_read_cmd(t_caps *caps)
{
  t_lol			cpl;
  struct passwd	*pwd;

  if (caps->buff[0] == 4 && caps->buff[1] == 0 && caps->buff[2] == 0 \
      && caps->buff[3] == 0)
    caps->ok = 0;
  if (caps->buff[0] == 27)
    exec_arrow(caps);
  if (caps->buff[0] == 127)
  {
    if (caps->cursor_pos > 0)
      caps->cmd = my_delete_char(caps);
    caps->nb_tab = 0;
    aff_cmd(caps);
  }
  if (caps->buff[0] == '\t' && ++(caps->nb_tab))
    if (caps->nb_tab > 1)
    {
      pwd = getpwuid(getuid());
      recup_key(str_to_wordtab_delim(get_info("PATH", caps->lenv), ":"), \
      pwd->pw_dir, caps, &cpl);
      exec_auto(caps, &cpl);
    }
}

void			aff_cmd(t_caps *caps)
{
  int			col;

  col = caps->cursor_pos + my_strlen(caps->prompt);
  tputs(tgetstr("dl", NULL), 1, my_put_getstr);
  tputs(tgetstr("cr", NULL), 1, my_put_getstr);
  my_printf("%s%s", caps->prompt, caps->cmd);
  tputs(tgoto(tgetstr("ch", NULL), 1, col), 1, my_put_getstr);
}
