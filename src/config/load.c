/*
** load.c for config in /home/closingin/Documents/Epitech/Rendu/Unix/42sh/src/config
**
** Made by      Rémi Weislinger
** Login        closingin
**
** Started on   May 09 18:13 2015 closingin
** Update       May 23 19:52 2015 closingin
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include "get_next_line.h"
#include "config.h"

int				open_rc(char *progname)
{
  int			rc;
  char			*path;
  struct passwd	*pwd;

  pwd = getpwuid(getuid());
  path = my_strinit(strlen(pwd->pw_dir) + strlen(CONFIG_FILE) + 2);
  path = strcat(path, pwd->pw_dir);
  path = strcat(path, "/");
  path = strcat(path, CONFIG_FILE);
  rc = open(path, O_RDWR);
  if (errno == EISDIR)
    fprintf(stderr, "%s: %s: Is a directory\n", progname, path);
  return (rc);
}

t_list			*load_rc(int rc)
{
  int			line;
  char			*s;
  t_list		*file;
  t_file		*file_entry;

  line = 0;
  file = NULL;
  if (rc != -1)
    while ((s = get_next_line(rc)) && ++line)
      if (s[0] != '#')
      {
        if (!(file_entry = malloc(sizeof(t_file))))
          return (NULL);
        file_entry->content = s;
        file_entry->line = line;
        list_pushbot(&file, (void *)file_entry);
      }
  return (file);
}

t_config		*init_rc(char *progname)
{
  t_config		*config;

  if (!(config = malloc(sizeof(t_config))))
    return (NULL);
  config->aliases = NULL;
  config->envvars = NULL;
  config->vars = NULL;
  config->file = load_rc(open_rc(progname));
  parse_rc(config);
  return (config);
}
