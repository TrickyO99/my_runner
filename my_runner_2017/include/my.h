/*
** EPITECH PROJECT, 2017
** my.h
** File description:
** prototypes
*/

#ifndef MY_H
#define MY_H

void	my_printf(char *format, ...);
void	my_putchar(char c);
void	my_put_nbr_base(int nb, char *base);
int	my_put_uint_base(unsigned int nb, char *base);
int	my_putstr(char const *str);
int	my_putStr(char const *str);
int	my_put_pointer(char const *str);
int	my_strlen(char const *str);
int	my_getnbr(char const *str);
int	main(int ac, char **av);

#endif  /* MY_H */
