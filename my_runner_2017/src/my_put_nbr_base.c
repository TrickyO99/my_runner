/*
** EPITECH PROJECT, 2017
** my_put_nbr_base
** File description:
** put nbr base
*/

#include "../include/my.h"

void	octal_case(int nb)
{
	int arr[3];
	int i = 2;
	int modulo;

	arr[0] = 0;
	arr[1] = 0;
	arr[2] = 0;
	while (nb > 0) {
		modulo = nb % 8;
		nb = nb / 8;
		arr[i] = modulo;
		i = i - 1;
	}
	my_put_nbr_base(arr[0], "0123456789");
	my_put_nbr_base(arr[1], "0123456789");
	my_put_nbr_base(arr[2], "0123456789");
}

void	my_put_nbr_base(int nb, char *base)
{
	int modulo;
	int res;
	int size = my_strlen(base);

	if (size == 8) {
		octal_case(nb);
	}
	if (nb < 0) {
		my_putchar ('-');
		nb = nb * (-1);
	}
	res = nb / size;
	modulo = nb % size;
	if (res > 0)
		my_put_nbr_base(res, base);
	my_putchar(base[modulo]);
}
