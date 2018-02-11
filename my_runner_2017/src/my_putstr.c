/*
** EPITECH PROJECT, 2017
** my_putstr.c
** File description:
** displays string of caracters
*/

#include "../include/my.h"

int	my_putstr(char const *str)
{
	int i = 0;

	while (str[i] != '\0') {
		my_putchar(str[i]);
		i++;
	}
	return (0);
}
