/*
** pars_list4.c for  in /home/robin_l/Divers/MiniShell/MYSHV2/MAIN
** 
** Made by Loic Robin
** Login   <robin_l@epitech.net>
** 
** Started on  Sun Mar  8 16:32:06 2015 Loic Robin
** Last update Sat May 23 18:04:15 2015 Loic Robin
*/

#include <unistd.h>
#include "list.h"
#include "pars.h"
#include "my.h"

char	*clear_word(char *str, int p, int lp)
{
  int	c;

  c = lp;
  while (c < p)
    {
      str[c] = ' ';
      c += 1;
    }
  return (str);
}

t_node	*end_outpath_and_getword(t_node *tmp, int word)
{
  if (word <= 1)
    tmp->token = DA;
  else
    tmp->token = CMD;
  return (tmp);
}

t_node	*set_in_and_redir(t_node *in, t_node *tmp, int *redir)
{
  *redir = 1;
  in = tmp;
  return (in);
}
