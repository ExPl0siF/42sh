/*
** env_list.c for  in /home/robin_l/Divers/MiniShell/MAIN
** 
** Made by Loic Robin
** Login   <robin_l@epitech.net>
** 
** Started on  Tue Jan 27 00:21:35 2015 Loic Robin
** Last update Sun May 10 19:31:51 2015 Loic Robin
*/

#include <stdlib.h>
#include <unistd.h>
#include "../include/list.h"
#include "../include/my.h"

int		get_nbnode_info(char *type, t_dlist *lenv)
{
  int		n;
  char		*word;
  t_node	*tmp;

  word = NULL;
  n = 0;
  tmp = lenv->first;
  while (tmp != NULL)
    {
      word = get_word_delim(word, tmp->str, "=", 1);
      if (my_strcmp(word, type) == 0)
	return (n);
      free(word);
      tmp = tmp->next;
      n = n + 1;
    }
  return (-1);
}

char		*get_info(char *type, t_dlist *lenv)
{
  char		*word;
  t_node	*tmp;

  word = NULL;
  tmp = lenv->first;
  while (tmp != NULL)
    {
      word = get_word_delim(word, tmp->str, "=", 1);
      if (my_strcmp(word, type) == 0)
	{
	  free(word);
	  word = get_word_delim(word, tmp->str, "=", 0);
	  return (word);
	}
      free(word);
      tmp = tmp->next;
    }
  return (NULL);
}

t_dlist		*env_in_list(char **env)
{
  t_dlist	*nlenv;
  int		n;
  char		*tmp;

  n = 0;
  nlenv = NULL;
  if (env == NULL)
    return (NULL);
  if ((nlenv = init_dlist(nlenv)) == NULL)
    return (NULL);
  while (env[n] != NULL)
    {
      tmp = NULL;
      tmp = env[n];
      if ((nlenv = insert_at_n(nlenv, tmp, 0, n)) == NULL)
	return (NULL);
      n = n + 1;
    }
  return (nlenv);
}

char		**list_in_env(char **env, t_dlist *lenv)
{
  char		**nenv;
  char		*str;
  t_node	*tmp;
  int		size;
  int		n;

  nenv = NULL;
  if ((nenv = malloc(sizeof(char*) * (lenv->length + 1))) == NULL)
    return (env);
  tmp = lenv->first;
  n = 0;
  while (tmp != NULL)
    {
      nenv[n] = NULL;
      str = tmp->str;
      size = my_strlen(str);
      if ((nenv[n] = strcatrealloc(nenv[n], str, size)) == NULL)
	return (env);
      tmp = tmp->next;
      n = n + 1;
    }
  nenv[n] = NULL;
  return (nenv);
}
