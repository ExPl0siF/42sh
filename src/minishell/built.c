/*
** shell_process2.c for  in /home/robin_l/Divers/MiniShell/MAIN
** 
** Made by Loic Robin
** Login   <robin_l@epitech.net>
** 
** Started on  Tue Jan 27 23:10:43 2015 Loic Robin
** Last update Sat May 23 18:08:22 2015 Loic Robin
*/

#include <stdlib.h>
#include <unistd.h>
#include "sh.h"

t_cmd	*my_env(t_cmd *cmd)
{
  if (cmd->lenv != NULL)
    show_dlist(cmd->lenv, 1);
  cmd->retour = 0;
  return (cmd);
}

t_dlist		*mod_info_env(char *info, char *str, t_dlist *lenv)
{
  int		nb;
  char		*tmp_str;
  t_node	*tmp;

  nb = get_nbnode_info(info, lenv);
  if ((tmp = cursor_to_n(lenv, nb)) == NULL)
    return (lenv);
  tmp_str = tmp->str;
  if (tmp_str != NULL)
    free (tmp_str);
  tmp->str = NULL;
  if ((tmp->str = strcatrealloc(tmp->str, str, my_strlen(str))) == NULL)
    return (lenv);
  return (lenv);
}

t_cmd	*my_unsetenv(t_cmd *cmd)
{
  int	nb;

  if (size_wordtab(cmd->tabx) != 2)
    my_fdputstr("unsetenv [NAME]\n", 2);
  else
    {
      if ((nb = get_nbnode_info(cmd->tabx[1], cmd->lenv)) < 0)
	{
	  cmd->retour = 2;
	  my_fdputstr("Auncune variable d'environnement nommée ", 2);
	  my_fdputstr(cmd->tabx[1], 2);
	  my_fdputchar('\n', 2);
	}
      else
	{
	  if ((cmd->lenv = destruct_node(cmd->lenv, nb)) == NULL)
	    return (cmd);
	  cmd->env = list_in_env(cmd->env, cmd->lenv);
	  cmd->retour = 0;
	}
    }
  return (cmd);
}

t_cmd		*my_getenv(t_cmd *cmd)
{
  int		nb;
  t_node	*tmp;

  if (size_wordtab(cmd->tabx) != 2)
    my_fdputstr("getenv [NAME]\n", 2);
  else
    {
      if ((nb = get_nbnode_info(cmd->tabx[1], cmd->lenv)) < 0)
	{
	  cmd->retour = 2;
	  my_fdputstr("Auncune variable d'environnement nommée ", 2);
	  my_fdputstr(cmd->tabx[1], 2);
	  my_fdputchar('\n', 2);
	}
      else
	{
	  tmp = cursor_to_n(cmd->lenv, nb);
	  my_putstr(tmp->str);
	  my_putchar('\n');
	  cmd->retour = 0;
	}
    }
  return (cmd);
}
