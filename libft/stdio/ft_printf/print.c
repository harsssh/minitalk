/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:06:14 by kemizuki          #+#    #+#             */
/*   Updated: 2023/05/24 13:40:37 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_stdio.h"
#include <stddef.h>
#include <unistd.h>

size_t	ft_putchar(char c)
{
	ft_putchar_fd(c, STDOUT_FILENO);
	return (1);
}

size_t	ft_putstr(char *s)
{
	if (s == NULL)
		return (ft_putstr("(null)"));
	ft_putstr_fd(s, STDOUT_FILENO);
	return (ft_strlen(s));
}
