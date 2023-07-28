/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:10:07 by kemizuki          #+#    #+#             */
/*   Updated: 2023/05/24 13:40:19 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"
#include "ft_string.h"
#include <unistd.h>

size_t	ft_putunbr_base(unsigned long long nbr, char *base)
{
	unsigned int	blen;
	size_t			len;

	blen = ft_strlen(base);
	if (nbr < blen)
		return (ft_putchar(base[nbr]));
	len = ft_putunbr_base(nbr / blen, base);
	len += ft_putunbr_base(nbr % blen, base);
	return (len);
}

size_t	ft_putnbr_base(long long nbr, char *base)
{
	unsigned int	blen;
	size_t			len;

	blen = ft_strlen(base);
	if (nbr >= 0)
		return (ft_putunbr_base(nbr, base));
	len = ft_putchar('-');
	if (nbr / blen != 0)
		len += ft_putunbr_base(-(nbr / blen), base);
	len += ft_putunbr_base(-(nbr % blen), base);
	return (len);
}
