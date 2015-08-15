/*
** my_tablen.c for string in /home/closingin/Documents/Epitech/My/string
**
** Made by      Rémi WEISLINGER
** Login        closingin
**
** Started on   Jan 30 13:40 2015 closingin
** Update       Jan 30 13:41 2015 closingin
*/

int		my_tablen(char **tab)
{
  int	i;

  i = -1;
  while (tab && tab[++i]);
  return (i);
}
