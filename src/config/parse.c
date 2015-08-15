/*
** parse.c for config in /home/closingin/Documents/Epitech/Rendu/Unix/42sh/src/config
**
** Made by      Rémi Weislinger
** Login        closingin
**
** Started on   May 19 13:33 2015 closingin
** Update       May 24 21:34 2015 closingin
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "my.h"

int			parse_quote(char **w)
{
  if (w[0][0] == '\'' && \
    w[my_tablen(w) - 1][my_strlen(w[my_tablen(w) - 1]) - 1] == '\'')
    return (1);
  else if (w[0][0] == '"' && \
    w[my_tablen(w) - 1][my_strlen(w[my_tablen(w) - 1]) - 1] == '"')
    return (1);
  return (0);
}

int			parse_alias(char *s, t_list **aliases)
{
  char		*sp;
  char		**w1;
  char		**w2;
  t_alias	*alias;

  s += 5;
  while ((*s == ' ' || *s == '\t') && s++);
  w1 = str_to_wordtab_delim(s, "=");
  sp = s + strlen(w1[0]) + 1;
  w2 = str_to_wordtab_delim(sp, " \t");
  if (!(alias = malloc(sizeof(t_alias))))
    return (-1);
  alias->name = strndup(w1[0], strlen(w1[0]));
  if (parse_quote(w2))
    alias->cmd = strndup(s + strlen(w1[0]) + 2, \
    strlen(s) - strlen(w1[0]) - 3);
  else
    alias->cmd = strdup(w2[0]);
  if (!check_exist_alias(alias, *aliases))
    list_pushbot(aliases, (void *)alias);
  my_free_wordtab(w1);
  my_free_wordtab(w2);
  return (0);
}

int			parse_var(char *s, t_list **vars)
{
  char		*sp;
  char		**w1;
  char		**w2;
  t_var		*var;

  w1 = str_to_wordtab_delim(s, "=");
  sp = s + strlen(w1[0]) + 1;
  w2 = str_to_wordtab_delim(sp, " \t");
  if (!(var = malloc(sizeof(t_var))))
    return (-1);
  var->name = strndup(w1[0], strlen(w1[0]));
  if (parse_quote(w2))
    var->content = strndup(s + strlen(w1[0]) + 2, \
    strlen(s) - strlen(w1[0]) - 3);
  else
    var->content = strdup(w2[0]);
  if (!check_exist_var(var, *vars))
    list_pushbot(vars, (void *)var);
  my_free_wordtab(w1);
  my_free_wordtab(w2);
  return (0);
}

int			parse_envvar(char *s, t_list **envvars)
{
  s += 6;
  while ((*s == ' ' || *s == '\t') && s++);
  parse_var(s, envvars);
  return (0);
}

void		parse_rc(t_config *config)
{
  t_list	*file_temp;
  t_file	*file;

  file_temp = config->file;
  while (file_temp)
  {
    file = (t_file *)file_temp->data;
    if (is_alias(file->content))
      parse_alias(file->content, &(config->aliases));
    else if (is_var(file->content))
      parse_var(file->content, &(config->vars));
    else if (is_envvar(file->content))
      parse_envvar(file->content, &(config->envvars));
    file_temp = file_temp->next;
  }
}
