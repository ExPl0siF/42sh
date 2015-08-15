/*
** main.c for  in /home/robin_l/Divers/42SH
**
** Made by Loic Robin
** Login   <robin_l@epitech.net>
**
** Started on  Sun May 10 19:19:49 2015 Loic Robin
** Last update Sun May 24 17:59:12 2015 Loic Robin
*/

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"
#include "my.h"
#include "pars.h"
#include "dtab.h"
#include "sh.h"
#include "history.h"

int	gere_saisie_error(t_shell *sh)
{
  if (nll == 0)
    {
      my_putchar('\n');
      sh->quit = 1;
      sh->retour = 0;
    }
  else
    nll = 0;
  return (0);
}

char	*reset_caps_correcstr(char *str, t_caps *caps)
{
  tcsetattr(0, 0, &(caps->save));
  init_sig();
  if (str[(my_strlen(str) - 1)] == '\n')
    str[(my_strlen(str) - 1)] = '\0';
  while (my_strstrint(str, "*") == 1)
    str = replace_star(str);
  my_putchar('\n');
  return (str);
}

int	shell(t_shell *sh, t_caps *caps)
{
  char		*str;
  t_dlist	*flcmd;
  t_lcmd	*lcmd;

  str = NULL;
  flcmd = NULL;
  lcmd = NULL;
  if ((str = my_read(caps)) == NULL || nll == 1)
    return ((gere_saisie_error(sh)));
  if ((str = reset_caps_correcstr(str, caps)) == NULL)
    return (ERROR_MALLOC);
  if ((flcmd = init_dlist(flcmd)) == NULL)
    return (ERROR_MALLOC);
  if ((flcmd = lex_cmd(flcmd, str)) == NULL)
    return (ERROR_MALLOC);
  if (sh->config != NULL)
    if ((flcmd = set_ali(sh->config->aliases, flcmd)) == NULL)
      return (ERROR_MALLOC);
  if ((check_lcmd(flcmd)) < 0)
    return (INVALID_CMD);
  if ((lcmd = surlex_cmd(lcmd, flcmd)) == NULL)
    return (ERROR_MALLOC);
  return (parse_lcmd(lcmd, sh));
}

void	first_init_tcaps(t_caps *caps)
{
  if (tcgetattr(0, &(caps->save)) == -1)
    return ;
  if (tcgetattr(0, &(caps->term)) == -1)
    return ;
  caps->term.c_lflag &= ~(ICANON | ECHO);
  caps->term.c_cc[VMIN] = 1;
  caps->term.c_cc[VTIME] = 0;
  caps->prompt = NULL;
  if (tgetent(NULL, "xterm") == -1)
    return ;
}

int		main(int ac, char **av, char **env)
{
  t_shell	sh;
  t_caps	caps;
  int		retour;

  init_shell(&sh);
  sh.config = init_rc(av[0]);
  retour = 0;
  first_init_tcaps(&caps);
  init_history(&caps);
  if ((sh.lenv = env_in_list(env)) == NULL)
    return (-1);
  if (sh.config != NULL && ac)
    envvar_in_sh(sh.config->envvars, sh.lenv);
  while (sh.quit == 0)
    {
      init_tcaps(&caps, sh.lenv);
      nll = 0;
      caps.prompt = prompt(caps.prompt, sh.config->vars, sh.config->envvars);
      init_sig();
      shell(&sh, &caps);
      retour = sh.retour;
    }
  tcsetattr(0, 0, &(caps.save));
  write_history(caps.hist);
  return (retour);
}
