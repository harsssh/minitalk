/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:42:37 by kemizuki          #+#    #+#             */
/*   Updated: 2023/05/24 15:01:31 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"
#include "ft_stdio.h"
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

static size_t	print_placeholder(const t_placeholder ph, va_list *args)
{
	if (ph.specifier == CHAR)
		return (ft_putchar((unsigned char)(va_arg(*args, int))));
	if (ph.specifier == STRING)
		return (ft_putstr(va_arg(*args, char *)));
	if (ph.specifier == DECIMAL)
		return (ft_putnbr_base(va_arg(*args, int), DECIMAL_BASE));
	if (ph.specifier == U_DECIMAL)
		return (ft_putunbr_base(va_arg(*args, unsigned int), DECIMAL_BASE));
	if (ph.specifier == HEX)
		return (ft_putunbr_base(va_arg(*args, unsigned int), HEX_BASE));
	if (ph.specifier == HEX_UP)
		return (ft_putunbr_base(va_arg(*args, unsigned int), HEX_BASE_UP));
	if (ph.specifier == POINTER)
	{
		ft_putstr_fd("0x", STDOUT_FILENO);
		return (2 + ft_putunbr_base((uintptr_t)va_arg(*args, void *),
				HEX_BASE));
	}
	if (ph.specifier == PERCENT)
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list			args;
	t_placeholder	ph;
	size_t			len;

	len = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format = parse_placeholder(&ph, format);
			len += print_placeholder(ph, &args);
		}
		else
			len += ft_putchar(*format++);
	}
	va_end(args);
	return (len);
}
