/*
** minishell/prompt.c for minishell in /home/closingin/Documents/Epitech/Rendu/Unix/42sh/src/minishell
**
** Made by      Rémi Weislinger
** Login        closingin
**
** Started on   May 23 20:53 2015 closingin
** Update       May 23 23:20 2015 closingin
*/

#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>
#include "config.h"
#include "get_next_line.h"
#include "my.h"

char			*my_hostname()
{
  int			fd;
  char			*s;

  if ((fd = open("/etc/hostname", O_RDONLY)) == -1)
    return (NULL);
  s = get_next_line(fd);
  close(fd);
  return (s);
}

char			*parse_prompt(char *s)
{
  int			i;
  char			*res;
  char			*cwd;
  char			*hst;
  struct passwd	*pwd;

  i = -1;
  res = NULL;
  cwd = getcwd(NULL, 0);
  pwd = getpwuid(getuid());
  hst = my_hostname();
  while (s[++i])
    if (s[i] == '\\' && s[i + 1] && s[i + 1] == 'u' && ++i)
      res = strcatrealloc(res, pwd->pw_name, strlen(pwd->pw_name));
    else if (s[i] == '\\' && s[i + 1] && s[i + 1] == 'w' && ++i)
      res = strcatrealloc(res, cwd, strlen(cwd));
    else if (s[i] == '\\' && s[i + 1] && s[i + 1] == 'h' && ++i)
      res = strcatrealloc(res, hst, strlen(hst));
    else
      res = strcatrealloc(res, s + i, 1);
  free(s);
  free(cwd);
  free(hst);
  return (res);
}

char			*prompt(char *act, t_list *vars, t_list *envvars)
{
  t_var			*var;

  if (act)
    free(act);
  while (vars && (var = (t_var *)vars->data))
  {
    if (!strcmp(var->name, "PS1"))
      return (parse_prompt(strdup(var->content)));
    vars = vars->next;
  }
  while (envvars && (var = (t_var *)envvars->data))
  {
    if (!strcmp(var->name, "PS1"))
      return (parse_prompt(strdup(var->content)));
    envvars = envvars->next;
  }
  return (parse_prompt(strdup("\\u: \\w $ ")));
}
