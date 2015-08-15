/*
** config.c for minishell in /home/closingin/Documents/Epitech/Rendu/Unix/42sh/src/minishell
**
** Made by      Rémi Weislinger
** Login        closingin
**
** Started on   May 23 20:05 2015 closingin
** Update       May 23 23:32 2015 closingin
*/

#include <stdlib.h>
#include "config.h"
#include "sh.h"

void		envvar_in_sh(t_list *envvars, t_dlist *lenv)
{
  t_var		*envvar;
  char		*s;

  while (envvars)
  {
    s = NULL;
    envvar = (t_var *)envvars->data;
    if (envvar->name == NULL || envvar->content == NULL)
      return ;
    if ((s = strcatrealloc(s, envvar->name, \
			   (my_strlen(envvar->name)))) == NULL)
      return ;
    if ((s = strcatrealloc(s, "=", 1)) == NULL)
      return ;
    if ((s = strcatrealloc(s, envvar->content, \
			   (my_strlen(envvar->content)))) == NULL)
      return ;
    if ((get_nbnode_info(envvar->name, lenv)) > 0)
      lenv = mod_info_env(envvar->name, s, lenv);
    else
      lenv = push_end(lenv, s, 0);
    envvars = envvars->next;
    free(s);
  }
}

char		*check_alias(t_list *listalias, char *cmd)
{
  char		*tmp;
  t_alias	*alias;

  tmp = cmd;
  if (tmp == NULL)
    return (NULL);
  while (listalias)
    {
      alias = (t_alias *)listalias->data;
      if (alias->name != NULL && alias->cmd != NULL)
	{
	  if (my_strcmp(alias->name, tmp) == 0)
	    {
	      tmp = NULL;
	      if ((tmp = \
		   strcatrealloc(tmp, alias->cmd, \
				 my_strlen(alias->cmd))) == NULL)
		return (NULL);
	      return (tmp);
	    }
	}
      listalias = listalias->next;
    }
  return (tmp);
}

void	set_cmd_ali(t_list *listalias, t_node *cmd)
{
  char	**tmp;
  char 	*new;
  int  	size;
  char 	*s;

  tmp = NULL;
  new = NULL;
  if ((tmp = str_to_wordtab_delim(cmd->str, " \t")) == NULL)
    return ;
  size = my_strlen(tmp[0]);
  if ((size_wordtab(tmp)) > 0)
    if ((s = check_alias(listalias, tmp[0])) == NULL)
      return ;
  if ((new = strcatrealloc(new, s, my_strlen(s))) == NULL)
    return ;
  if ((new = strcatrealloc(new, &(cmd->str[size]), \
			   my_strlen(&(cmd->str[size])))) == NULL)
    return ;
  cmd->str = new;
  clean_wordtab(tmp);
}

t_dlist		*set_ali(t_list *listalias, t_dlist *lcmd)
{
  t_node	*cmd;

  cmd = lcmd->first;
  while (cmd != NULL)
    {
      if (cmd->token == CMD && cmd->str != NULL)
	set_cmd_ali(listalias, cmd);
      cmd = cmd->next;
    }
  return (lcmd);
}
