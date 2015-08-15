/*
** lexem.c for  in /home/robin_l/Divers/42SH
** 
** Made by Loic Robin
** Login   <robin_l@epitech.net>
** 
** Started on  Sun May 10 21:53:39 2015 Loic Robin
** Last update Tue May 19 23:59:26 2015 Loic Robin
*/

#include "pars.h"

t_lexlist       loperator[NB_OPERATOR] =
  {{";", SEMICOLON},
   {"<", LCHEV},
   {"<<", LDCHEV},
   {">", RCHEV},
   {">>", RDCHEV},
   {"|", PIPE},
   {"&&", AND},
   {"||", OR}};

t_lexptrfct     lbuiltin[NB_BUILTIN] =
  {{"echo", &my_echo},
   {"exit", &leave},
   {"env", &my_env},
   {"getenv", &my_getenv},
   {"setenv", &my_setenv},
   {"unsetenv", &my_unsetenv},
   {"cd", &cd}};
