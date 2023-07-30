/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 00:41:54 by kemizuki          #+#    #+#             */
/*   Updated: 2023/07/31 00:41:56 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stddef.h"

int	ft_strall(char *str, int (*f)(char))
{
	if (str == NULL || f == NULL)
		return (0);
	while (*str)
	{
		if (!f(*str))
			return (0);
		str++;
	}
	return (1);
}
