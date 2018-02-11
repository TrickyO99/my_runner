/*
** EPITECH PROJECT, 2017
** disp
** File description:
** stdarg
*/

#include <stdarg.h>
#include "../include/my.h"

void	hashtag(int i, va_list ap, char *format)
{
	if (format[i + 2] == 'o') {
		my_putchar('0');
		my_put_nbr_base(va_arg(ap, int), "01234567");
		i = i + 1;
	}
	if (format[i + 2] == 'x') {
		my_putstr("0x");
		my_put_nbr_base(va_arg(ap, int), "0123456789abcdef");
		i = i + 1;
	}
	if (format[i + 2] == 'X') {
		my_putstr("0X");
		my_put_nbr_base(va_arg(ap, int), "0123456789abcdef");
		i = i + 1;
	}
}

void	reduction3(int i, va_list ap, char *format)
{
	if (format[i + 1] == 'S') {
		my_putStr(va_arg(ap, char *));
		i = i + 1;
	}
	if (format[i + 1] == '%') {
		i = i + 1;
	}
	if (format[i] == '%') {
		if (format[i + 1] != '%' && format[i + 1] != 'S' &&
			format[i + 1] != 'b' && format[i + 1] != 'p' &&
			format[i + 1] != 's' && format[i + 1] != 'c' &&
			format[i + 1] != 'u' && format[i + 1] != 'x' &&
			format[i + 1] != 'o' && format[i + 1] != 'd' &&
			format[i + 1] != 'i' && format[i + 1] != 'X') {
			my_putchar(format[i]);
			my_putchar(format[i + 1]);
			i = i + 1;
		}
	}
}

void	reduction2(int i, va_list ap, char *format)
{
	if (format[i + 1] == 'c') {
		my_putchar(va_arg(ap, int));
		i = i + 1;
	}
	if (format[i + 1] == 's') {
		my_putstr(va_arg(ap, char *));
		i = i + 1;
	}
	if (format[i + 1] == 'p') {
		my_put_pointer(va_arg(ap, char *));
		i = i + 1;
	}
	if (format[i + 1] == 'b') {
		my_put_nbr_base(va_arg(ap, int), "01");
		i = i + 1;
	}
	reduction3(i, ap, format);
}

void	reduction(int i, va_list ap, char *format)
{
	if (format[i + 1] == 'd' || format[i + 1] == 'i') {
		my_put_nbr_base(va_arg(ap, int), "0123456789");
		i = i + 1;
	}
	if (format[i + 1] == 'o') {
		my_put_nbr_base(va_arg(ap, int), "01234567");
		i = i + 1;
	}
	if (format[i + 1] == 'x' || format[i + 1] == 'X') {
		my_put_nbr_base(va_arg(ap, int), "0123456789abcdef");
		i = i + 1;
	}
	if (format[i + 1] == 'u') {
		my_put_uint_base(va_arg(ap, unsigned int), "0123456789");
		i = i + 1;
	}
	reduction2(i, ap, format);
}

void	my_printf(char *format, ...)
{
	int i = 0;
	va_list ap;

	va_start(ap, format);
	while (format[i] != '\0') {
		if (format[i] == '%' && format[i - 1] != '%') {
			if (format[i + 1] == '#') {
				hashtag(i, ap, format);
				i = i + 2;
			}
			reduction(i, ap, format);
			i = i + 2;
		} else {
			my_putchar(format[i]);
			i = i + 1;
		}
	}
	va_end(ap);
}
