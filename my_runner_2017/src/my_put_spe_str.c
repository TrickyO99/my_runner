/*
** EPITECH PROJECT, 2017
** my_putSTR
** File description:
** my_putstr but for S
*/

#include "../include/my.h"

int	my_putStr(char const *str)
{
	int i = 0;

	while (str[i] != '\0') {
		if (str[i] >= 32 && str[i] < 127) {
			my_putchar(str[i]);
			i = i + 1;
		} else {
			my_putchar('\\');
			my_put_nbr_base(str[i], "01234567");
			i = i + 1;
		}
	}
	return (0);
}
