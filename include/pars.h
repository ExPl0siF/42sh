/*
** pars.h for  in /home/robin_l/Divers/42SH
** 
** Made by Loic Robin
** Login   <robin_l@epitech.net>
** 
** Started on  Sun May 10 21:54:40 2015 Loic Robin
** Last update Sat May 23 22:09:49 2015 Loic Robin
*/

#ifndef _PARS_H_
#define _PARS_H_
#include "sh.h"

typedef struct  s_lexptrfct
{
  char          *str;
  t_cmd		*(*fct)(t_cmd *cmd);
}               t_lexptrfct;

typedef struct  s_lexlist
{
  char          *str;
  int           token;
}               t_lexlist;

t_cmd	*cd(t_cmd *cmd);
t_cmd	*leave(t_cmd *cmd);
t_cmd	*my_env(t_cmd *cmd);
t_cmd	*my_setenv(t_cmd *cmd);
t_cmd	*my_unsetenv(t_cmd *cmd);
t_cmd	*my_getenv(t_cmd *cmd);
t_cmd	*my_echo(t_cmd *cmd);

extern	t_lexlist	loperator[NB_OPERATOR];
extern	t_lexptrfct     lbuiltin[NB_BUILTIN];

#endif /* !_PARS_H_ */
