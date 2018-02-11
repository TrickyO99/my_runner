/*
** EPITECH PROJECT, 2017
** my put pointer
** File description:
** prints pointer
*/

#include "../include/my.h"

int	my_put_pointer(char const *str)
{
	int oui = my_getnbr(str);

	my_putchar('0');
	my_putchar('x');
	my_put_nbr_base(oui, "0123456789abcdef");
	return (0);
}
