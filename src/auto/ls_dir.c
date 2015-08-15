/*
** main.c for  in /home/ExPl0siF/Bin/base_directory
**
** Made by Theo Caselli
** Login   <casell_t@epitech.net>
**
** Started on  Wed May  6 13:34:46 2015 Theo Caselli
** Last update Fri May 22 22:55:38 2015 Theo Caselli
*/

#include <sys/types.h>
#include <termios.h>
#include <ncurses.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <term.h>
#include <history.h>
#include <dtab.h>
#include <my.h>

int	my_ls_three(char *buff, t_lol *l_tab, int k, struct dirent *ent)
{
  if (check_point(buff) == 0 || buff[0] == '/')
    {
      check_list(l_tab, ent->d_name, k, buff);
      k++;
    }
  else if (strncmp(ent->d_name, buff, my_strlen(buff)) == 0)
    {
      check_list(l_tab, ent->d_name, k, buff);
      k++;
    }
  return (k);
}

int		my_ls_two(char *tmp, char *buff, t_lol *l_tab)
{
  int		k;
  struct dirent	*ent;

  k = -1;
  if (l_tab->dir != NULL)
    while ((ent = readdir(l_tab->dir)) != NULL)
      if (my_strlen(tmp) != 0)
	{
	  if (strncmp(ent->d_name, tmp, my_strlen(tmp)) == 0)
	    {
	      check_list(l_tab, ent->d_name, k, buff);
	      k++;
	    }
	  else if (tmp[my_strlen(tmp) - 1] == '/')
	    {
	      check_list(l_tab, ent->d_name, k, buff);
	      k++;
	    }
	}
      else
	k += my_ls_three(buff, l_tab, k, ent);
  return (k);
}

int    	my_ls(char *buff, t_lol *l_tab)
{
  int  	i;
  DIR  	*dir;
  char 	*tmp;

  i = my_strlen(buff) + 1;
  tmp = NULL;
  if (my_strstrint(buff, "/") == 1)
    {
      if (buff[i - 2] != '/')
	while (buff[--i] != '/');
      else
	i = -1;
    }
  else
    i = -1;
  ++i;
  tmp = strcatrealloc(tmp, &buff[i], my_strlen(&buff[i]));
  dir = NULL;
  dir = open_direct(buff, i, dir);
  l_tab->dir = dir;
  if (my_ls_two(tmp, buff, l_tab) == -1)
    return (0);
  return (1);
}

void	recup_key_two(char **tab_path, char *home, char *buff, t_lol *l_tab)
{
  if (strncmp(buff, "~/", 2) == 0)
    buff = reset_buff(buff, home);
  if (strncmp(buff, "../", 3) != 0 &&
      strncmp(buff, "./", 2) != 0 && strncmp(buff, "/", 1) != 0
      && strncmp(buff, "~/", 2) != 0)
    {
      if (check_binaire(tab_path, buff, l_tab) == -1)
	my_ls(buff, l_tab);
    }
  else
    my_ls(buff, l_tab);
}

int    	recup_key(char **tab_path, char *home, t_caps *save, t_lol *l_tab)
{
  char 	*buff;

  l_tab->list = NULL;
  l_tab->nb_item = 0;
  if (save->cmd != NULL && my_strlen(save->cmd) != 0)
    {
      buff = save_util(save->cmd, save->cursor_pos);
      if (buff != NULL && my_strlen(buff) != 0)
	{
	  if (tab_path != NULL && home != NULL)
	    recup_key_two(tab_path, home, rm_n(buff), l_tab);
	  else
	    my_ls(rm_n(buff), l_tab);
	}
      else
	{
	  buff = strcatrealloc(buff, "./", 2);
	  my_ls(buff, l_tab);
	}
    }
  return (0);
}
