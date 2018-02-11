/*
** EPITECH PROJECT, 2017
** my_strlen.c
** File description:
** count the number of caracters in a string
*/

#include "../include/my.h"

int	my_strlen(char const *str)
{
	int i = 0;

	while (str[i] != '\0') {
		i++;
	}
	return (i);
}
