/*
** load_command_tab.c for  in /home/robin_l/Divers/MiniShell/MYSHV2/MAIN
** 
** Made by Loic Robin
** Login   <robin_l@epitech.net>
** 
** Started on  Sun Mar  1 22:58:03 2015 Loic Robin
** Last update Sat May 23 23:23:40 2015 Loic Robin
*/

#include <stdlib.h>
#include <unistd.h>
#include "pars.h"
#include "sh.h"

void    clean_tabpathcmd(char **tabx, char *path)
{
  if (tabx != NULL)
    {
      clean_wordtab(tabx);
      free(tabx);
    }
  if (path != NULL)
    free(path);
}

t_node		*get_cmd_op(t_dlist *lcmd, int *tok, int n)
{
  t_node	*tmp;

  if ((tmp = cursor_to_n(lcmd, n)) == NULL)
    return (NULL);
  if (tmp->token != CMD && tmp->token != BUILTIN)
    tmp->token = DA;
  while (tmp != NULL)
    {
      if (tmp->token == CMD || tmp->token == BUILTIN)
	{
	  *tok = tmp->token;
	  tmp->token = DA;
	  return (tmp);
	}
      if (tmp->token > DA)
	return (NULL);
      tmp = tmp->prev;
    }
  return (NULL);
}

char	*cmd_color(char *cmd)
{
  char	*test;
  int	p;
  int	first;
  int	lp;

  p = 0;
  test = NULL;
  first = 0;
  while (cmd[p] != '\0' && first == 0)
    {
      while (cmd[p] != '\0' && (is_delim(cmd[p], " \t")) == 1)
	p += 1;
      lp = p;
      while (cmd[p] != '\0' && (is_delim(cmd[p], " \t")) == 0)
	p += 1;
      if ((p - lp) > 0)
	{
	  if ((test = strcatrealloc(test, &cmd[lp], (p - lp))) == NULL)
	    return (cmd);
	  first = 1;
	  if ((my_strcmp(test, "ls")) == 0 || (my_strcmp(test, "grep")) == 0)
	    return ((cmd = strcatrealloc(cmd, " --color=auto \n", 13)));
	}
    }
  return (cmd);
}

t_cmd		*load_command_tab(t_cmd *cmd, t_dlist *lcmd, int n)
{
  t_node	*node_cmd;
  int		token;

  cmd->ok = -1;
  cmd->tabx = NULL;
  token = 0;
  if ((node_cmd = get_cmd_op(lcmd, &token, n)) == NULL)
    return (NULL);
  if (node_cmd->str == NULL)
    return (NULL);
  if (token == CMD && node_cmd->path == NULL)
    cmd->ok = -1;
  else
    cmd->ok = 1;
  cmd->type = token;
  cmd->path = node_cmd->path;
  if ((node_cmd->str = cmd_color(node_cmd->str)) == NULL)
    return (NULL);
  if ((cmd->tabx = str_to_wordtab_delim(node_cmd->str, " \t")) == NULL)
    return (NULL);
  cmd->error = node_cmd->ok;
  return (cmd);
}
