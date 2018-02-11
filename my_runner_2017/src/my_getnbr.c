/*
** EPITECH PROJECT, 2017
** Getnbr
** File description:
** My_getnbr
*/

#include <stdlib.h>
#include "../include/my.h"

int my_getnbr(char const *str)
{
	int var = 0;
	int inv = 1;
	int i = 0;

	if (str == NULL)
		return (0);
	while ((*str < 47 || *str > 58) && *str != 0) {
		str = str + 1;
		i = i + 1;
	}
	if (i > 0 && *(str - 1) == 45)
		inv = -1;
	while (*str != 0 && *str >= '0' && *str <= '9') {
		var *= 10;
		var += *str - 48;
		str += 1;
	}
	var *= inv;
	return (var);
}
