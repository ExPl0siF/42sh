/*
** my.h for  in /home/robin_l/rendu/Piscine_C_J09/include
**
** Made by Loic Robin
** Login   <robin_l@epitech.net>
**
** Started on  Thu Oct  9 10:36:59 2014 Loic Robin
** Last update Wed May 13 16:29:41 2015 Gaetan THEROU
*/

#ifndef _MY_H_
#define _MY_H_

#include <stdarg.h>

void	my_putchar(char c);
void	my_sort_int_tb(int *tb, int size);
int	my_isneg(int nb);
int	my_put_nbr(int nb);
int	my_swap(int *a, int *b);
int	my_putstr(char *str);
int	my_strlen(char *str);
int	my_getnbr(char *str);
int	my_ngetnbr(char *str, char *base, int *neg);
double	my_dgetnbr(char *str);
int	my_power_rec(int nb, int power);
int	my_square_root(int nb);
int	my_is_prime(int nombre);
int	my_find_prime_sup(int nb);
char	*my_strcpy(char *dest, char *src);
char	*my_strncpy(char *dest, char *src, int nb);
char	*my_revstr(char *str);
char	*my_strstr(char *str, char *to_find);
int	my_strcmp(char *s1, char *s2);
int	my_strncmp(char *s1, char *s2, int nb);
char	*my_strupcase(char *str);
char	*my_strlowcase(char *str);
char	*my_strcapitalize(char *str);
int	my_str_isalpha(char *str);
int	my_str_isnum(char *str);
int	my_str_islower(char *str);
int	my_str_isupper(char *str);
int	my_str_isprintble(char *str);
int	my_showstr(char *str);
int	my_showmem(char *str, int size);
char	*my_strcat(char *dest, char *src);
char	*my_strncat(char *dest, char *src, int nb);
int	my_strlcat(char *dest, char *src, int size);
char	**my_str_to_wordtb(char *str);
int	my_show_wordtab(char **tb);
char	*my_memset(char *str, char d, int size);
char	*str_safealloc(char *str, int size);
int	count_div_base(unsigned long nb, char *base);
int	putnbr_base(unsigned long nb, char *base);
int	my_getnbr_based(char *str, char *base);
int	count_div_based(long nb, char *base);
char	*nb_inf_lenb(char *test, char *base, int first);
char	*putnbr_based(long nb, char *base);
char	*convert_based(char *nbr, char *base_from, char* base_to);
int	count_div(long nb);
int	my_putlong(long nb);
void	my_putalpha(char *str);
int	sizel(const char *str, int pos);
void	reset_place(int begin, int *pos, const char *format);
char	*get_t(const char *str, int *pos, int size, char *test);
int	count_arg(const char *format);
void	print_var(int *pos, const char *format, va_list valist, int *nb_var);
int	special_prct(const char *str, int *pos);
int	my_printf(const char *format, ...);
char	*reallocpy(char *dest, int new_size);
char	*strcatrealloc(char *dest, char *src, int size_src);
void	my_fdputchar(char d, int fd);
void	my_fdputstr(char *str, int fd);
int	my_fdput_nbr(int nb, int fd);
char	*get_word_delim(char *word, char *str, char *delim, int n);
char	**str_to_wordtab_delim(char *str, char *delim);
int	size_wordtab(char **tb);
void	clean_wordtab(char **tb);
int	is_delim(char d, char *delim);
char	*clean_str(char *str, char *clean);
int	nb_div(int nb, int div);
int		my_putcolor(char *, int);

#endif /* !MY_H_ */
