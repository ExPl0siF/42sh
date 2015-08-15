/*
** built_echo.c for  in /home/robin_l/Divers/PSU_2014_42sh
** 
** Made by Loic Robin
** Login   <robin_l@epitech.net>
** 
** Started on  Sat May 23 22:55:03 2015 Loic Robin
** Last update Sun May 24 00:06:21 2015 Loic Robin
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include "sh.h"

t_esc   	*create_esc()
{
  t_esc		*esc;

  if (!(esc = malloc(sizeof(t_esc) * 10)))
    return (NULL);
  esc[0].s = strdup("\\a");
  esc[0].c = '\a';
  esc[1].s = strdup("\\b");
  esc[1].c = '\b';
  esc[2].s = strdup("\\c");
  esc[2].c = '\0';
  esc[3].s = strdup("\\f");
  esc[3].c = '\f';
  esc[4].s = strdup("\\n");
  esc[4].c = '\n';
  esc[5].s = strdup("\\r");
  esc[5].c = '\r';
  esc[6].s = strdup("\\t");
  esc[6].c = '\t';
  esc[7].s = strdup("\\v");
  esc[7].c = '\v';
  esc[8].s = strdup("\\\\");
  esc[8].c = '\\';
  esc[9].s = NULL;
  return (esc);
}

void		check_var_env(char *cmd, t_dlist *lenv)
{
  char		*s;
  char		*var_info;

  s = NULL;
  var_info = NULL;
  if (cmd[1] == '\0')
    return;
  if ((s = strcatrealloc(s, &(cmd[1]), my_strlen(&(cmd[1])))) == NULL)
    return ;
  if ((var_info = get_info(s, lenv)) == NULL)
    return ;
  my_fdputstr(var_info, 1);
}

int		my_echo_e(t_cmd *cmd)
{
  int	i;
  int	j;
  int	k;
  char	*s;
  t_esc	*esc;

  i = 1;
  s = NULL;
  esc = create_esc();
  while (cmd->tabx[++i] && (j = -1))
    while (cmd->tabx[i][++j] && (k = -1))
      if (cmd->tabx[i][j] == '\\' && cmd->tabx[i][j + 1])
        while (esc[++k].s)
          if (!strncmp(esc[k].s, cmd->tabx[i] + j, 2))
          {
            cmd->tabx[i][j] = esc[k].c;
            s = strcatrealloc(s, cmd->tabx[i], j + 1);
            if (*(cmd->tabx[i] + j + 2))
              s = strcatrealloc(s, cmd->tabx[i] + j + 2, \
              strlen(cmd->tabx[i]) - j);
            else
              *(cmd->tabx[i] + j + 1) = 0;
            cmd->tabx[i] = s;
          }
  return (2);
}

void	set_ibn(int *i, int *bn)
{
  *i += 1;
  *bn = 0;
}

t_cmd	*my_echo_one(t_cmd *cmd)
{
  int	i;
  int	bn;

  bn = 1;
  i = 1;
  if ((my_strcmp(cmd->tabx[1], "-e")) == 0)
    i = my_echo_e(cmd);
  else if ((my_strcmp(cmd->tabx[1], "-n")) == 0)
    set_ibn(&i, &bn);
  while (cmd->tabx[i] != NULL)
  {
    if (my_strcmp(cmd->tabx[i], "$?") == 0)
      my_printf("%d", cmd->retour);
    else if (cmd->tabx[i][0] == '$')
      check_var_env(cmd->tabx[i], cmd->lenv);
    else
      my_fdputstr(cmd->tabx[i], 1);
    i += 1;
    if (cmd->tabx[i] != NULL)
      my_fdputchar(' ', 1);
  }
  if (bn == 1)
    my_fdputchar('\n', 1);
  return (cmd);
}
