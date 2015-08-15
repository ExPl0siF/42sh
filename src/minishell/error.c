/*
** error.c for  in /home/robin_l/Divers/42SH
** 
** Made by Loic Robin
** Login   <robin_l@epitech.net>
** 
** Started on  Sun May 10 21:46:16 2015 Loic Robin
** Last update Sat May 23 18:01:55 2015 Loic Robin
*/

#include <stdlib.h>
#include "my.h"
#include "list.h"
#include "pars.h"
#include "sh.h"

void    show_token(int token)
{
  int   c;

  c = 0;
  while (c <= NB_OPERATOR)
    {
      if (loperator[c].token == token)
        my_putstr(loperator[c].str);
      c += 1;
    }
  c = 0;
}

t_dlist         *check_empty(t_dlist *lcmd)
{
  t_node        *tmp;
  int           ok;
  int           c;
  int           n;

  tmp = lcmd->first;
  n = 0;
  while (tmp != NULL)
    {
      c = 0;
      ok = 1;
      if (tmp->str == NULL)
        tmp->token = DA;
      while (tmp->str[c] != '\0' && ok == 1)
        {
          if (tmp->str[c] != ' ' && tmp->str[c] != '\t')
            ok = 0;
          c += 1;
        }
      if (ok == 1)
        lcmd = destruct_node(lcmd, n);
      tmp = tmp->next;
      n += 1;
    }
  return (lcmd);
}

int		end_check_lcmd(int ltok)
{
  if (ltok == LDCHEV || ltok == LCHEV || ltok == RCHEV || ltok == RDCHEV)
    {
      my_putstr("bash: syntax error near unexpected token `newline'");
      my_putstr("\n");
      return (-1);
    }
  else if (ltok == PIPE || ltok == AND || ltok == OR)
   {
      my_putstr("bash: syntax error near unexpected token `newline'");
      my_putstr("\n");
      return (-1);
   }
  return (1);
}

int	condition_error(int ltok, int tok)
{
  int	error;

  error = 0;
  if (ltok == -2)
    {
      if (tok == SEMICOLON || tok == PIPE || tok == AND || tok == OR)
	error = 1;
    }
  else
    {
      if (tok != CMD && tok != BUILTIN && tok != PATH)
	if (ltok != CMD && ltok != BUILTIN && ltok != PATH)
	  error = 1;
      if (tok == SEMICOLON || tok == AND || tok == OR)
	if (ltok != CMD && ltok != BUILTIN && ltok != PATH)
	  error = 1;
    }
  if (error)
    {
      my_putstr("bash: syntax error near unexpected token `");
      show_token(tok);
      my_putstr("'\n");
    }
  return (error);
}

int             check_lcmd(t_dlist *lcmd)
{
  t_node        *tmp;
  int           ltok;

  ltok = -2;
  if (lcmd == NULL || (tmp = lcmd->first) == NULL)
    return (-1);
  lcmd = check_empty(lcmd);
  while (tmp != NULL)
    {
      if (tmp->token <= 0)
        {
          my_printf("bash: syntax error "\
		    "near unexpected token `%s'\n", tmp->str);
          return (-1);
        }
      if ((condition_error(ltok, tmp->token)) == 1)
	return (-1);
      ltok = tmp->token;
      tmp = tmp->next;
    }
  return (end_check_lcmd(ltok));
}
