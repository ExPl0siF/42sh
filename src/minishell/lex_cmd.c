/*
** lex_cmd.c for  in /home/robin_l/Divers/42OOK
** 
** Made by Loic Robin
** Login   <robin_l@epitech.net>
** 
** Started on  Fri May 22 21:44:31 2015 Loic Robin
** Last update Fri May 22 21:50:30 2015 Loic Robin
*/

#include <stdlib.h>
#include <unistd.h>
#include "list.h"
#include "sh.h"
#include "pars.h"
#include "my.h"

char    *set_word(char *word, char *str, int size)
{
  if ((word = strcatrealloc(word, str, size)) == NULL)
    return (NULL);
  if ((word = clean_word(word)) == NULL)
    return (NULL);
  return (word);
}

t_dlist *new_word_inlist(t_dlist *list, int *n, char *str, int size)
{
  char  *word;
  char  *test;
  int   token;
  int   l;
  int   p;

  word = NULL;
  test = NULL;
  l = -1;
  token = CMD;
  p = -1;
  if ((word = set_word(word, str, size)) == NULL)
    return (list);
  while (word[++p] != '\0' && is_delim(word[p], " \t") == 0);
  if ((test = strcatrealloc(test, word, p)) == NULL)
    return (NULL);
  while (++l < NB_BUILTIN && token == CMD)
    if (p > 0 && (my_strcmp(test, lbuiltin[l].str)) == 0)
      token = BUILTIN;
  if ((list = insert_at_n(list, word, token, *n)) == NULL)
    return (NULL);
  free(word);
  free(test);
  *n = *n + 1;
  return (list);
}

t_dlist *new_delim_inlist(t_dlist *list, int *n, char *str, int size)
{
  int   l;
  int   token;
  char  *delim;

  l = 0;
  token = 0;
  delim = NULL;
  if ((delim = strcatrealloc(delim, str, size)) == NULL)
    return (NULL);
  if ((delim = clean_word(delim)) == NULL)
    return (NULL);
  while (l < NB_OPERATOR && token == 0)
    {
      if ((my_strcmp(delim, loperator[l].str)) == 0)
        token = loperator[l].token;
      l += 1;
    }
  if ((list = insert_at_n(list, delim, token, *n)) == NULL)
    return (NULL);
  if (delim != NULL)
    free(delim);
  *n = *n + 1;
  return (list);
}

t_dlist         *end_lex_cmd(t_dlist *list)
{
  t_node        *tmp;
  int           n;

  if (list->length == 0)
    return (NULL);
  tmp = list->first;
  n = 1;
  while (tmp != NULL)
    {
      if (tmp->token == RCHEV || tmp->token == RDCHEV \
          || tmp->token == LCHEV || tmp->token == LDCHEV)
        {
          if (tmp->next != NULL && tmp->next->str != NULL \
              && tmp->next->token == CMD)
            if ((list = gere_path(list, tmp->next->str, n)) == NULL)
              return (NULL);
        }
      tmp = tmp->next;
      n += 1;
    }
  return (list);
}

t_dlist         *lex_cmd(t_dlist *list, char *str)
{
  int           p;
  int           lp;
  int           n;

  n = 0;
  p = 0;
  while (str[p] != '\0')
    {
      lp = p;
      while ((is_delim(str[p], DELIM)) == 1 && str[p] != '\0')
        p += 1;
      if (lp != p)
        if ((list = new_delim_inlist(list, &n, &str[lp], (p - lp))) == NULL)
          return (NULL);
      lp = p;
      while ((is_delim(str[p], DELIM)) == 0 && str[p] != '\0')
        p += 1;
      if (lp != p)
        if ((list = new_word_inlist(list, &n, &str[lp], (p - lp))) == NULL)
          return (NULL);
    }
  if ((list = end_lex_cmd(list)) == NULL)
    return (NULL);
  return (list);
}
