/*
** gere_sig.c for  in /home/robin_l/Divers/42OOK
** 
** Made by Loic Robin
** Login   <robin_l@epitech.net>
** 
** Started on  Fri May 22 22:21:15 2015 Loic Robin
** Last update Sat May 23 19:08:29 2015 Loic Robin
*/

#include <signal.h>
#include "sh.h"

void    segv()
{
  my_putstr("Segmentation Fault\n");
}

void    inhib_signal()
{
  signal(SIGSEGV, segv);
}

