/*
** list.h for  in /home/robin_l/Divers/Pushswap/include
** 
** Made by Loic Robin
** Login   <robin_l@epitech.net>
** 
** Started on  Sun Nov 30 17:51:24 2014 Loic Robin
** Last update Thu May 21 22:50:46 2015 Loic Robin
*/

#ifndef _LIST_H_
#define _LIST_H_

typedef struct	s_node t_node;
typedef struct	s_dlist t_dlist;

struct		s_node
{
  char		*str;
  char		*path;
  int		token;
  int		fd;
  int		ok;
  t_node	*next;
  t_node	*prev;
};

struct		s_dlist
{
  int		length;
  t_node	*first;
  t_node	*last;
};

t_dlist	*init_dlist(t_dlist *list);
void	destruct_dlist(t_dlist **list);
t_dlist	*destruct_last_node(t_dlist *list);
t_dlist	*destruct_first_node(t_dlist *list);
t_dlist	*destruct_center_node(t_dlist *list, int nb_node);
t_dlist	*destruct_node(t_dlist *list, int nb_node);
t_dlist *insert_at_n(t_dlist *list, char *str, int token, int n);
t_dlist	*push_begin(t_dlist *list, char *str, int token);
t_dlist	*push_end(t_dlist *list, char *str, int token);
t_node	*get_position(t_dlist *list, t_node *node, int n);
t_node	*cursor_to_n(t_dlist *list, int n);
void	show_dlist(t_dlist *list, int fd);
int	get_nbnode_info(char *type, t_dlist *lenv);

#endif /* !_LIST_H_ */
