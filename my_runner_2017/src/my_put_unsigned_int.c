/*
** EPITECH PROJECT, 2017
** my_put_unsigned_int
** File description:
** yup
*/

#include "../include/my.h"

int	my_put_uint_base(unsigned int nb, char *base)
{
	unsigned int modulo;
	unsigned int res;
	int size = my_strlen(base);

	res = nb / size;
	modulo = nb % size;
	if (res > 0)
		my_put_nbr_base(res, base);
	my_putchar(base[modulo]);
	return (0);
}
