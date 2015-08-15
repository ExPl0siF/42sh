/*
** process.h for  in /home/robin_l/Divers/MiniShell/MAIN
** 
** Made by Loic Robin
** Login   <robin_l@epitech.net>
** 
** Started on  Mon Jan 26 22:07:04 2015 Loic Robin
** Last update Thu Feb 19 19:13:53 2015 Loic Robin
*/

#ifndef _PROCESS_H_
#define	_PROCESS_H_

#include "shell.h"
#include "list.h"
#define S_PRO 6

typedef struct  s_ptrf
{
  char		*str;
  t_shell	*(*fct)();
}               t_ptrf;

t_shell	*cd(t_shell *sh);
t_shell	*leave(t_shell *sh);
t_shell	*my_env(t_shell *sh);
t_shell	*my_setenv(t_shell *sh);
t_shell	*my_unsetenv(t_shell *sh);
t_shell	*my_getenv(t_shell *sh);

t_ptrf process_tab[S_PRO] = {{"cd", &cd}, \
			     {"exit", &leave}, \
			     {"env", &my_env}, \
			     {"setenv", &my_setenv}, \
			     {"unsetenv", &my_unsetenv}, \
			     {"getenv", &my_getenv}};

#endif /* !_PROCESS_H_ */
