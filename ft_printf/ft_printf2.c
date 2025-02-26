/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:11:36 by pbourgeo          #+#    #+#             */
/*   Updated: 2023/11/06 14:24:18 by pbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_put_pointer(void *p, int *nb)
{
	size_t	n;

	if (p)
	{
		n = (size_t)p;
		ft_putchar('0', nb);
		ft_putchar('x', nb);
		ft_putnbr_pointer(n, nb);
	}
	else
		ft_putstr("(nil)", nb);
}

void	ft_putnbr_pointer(size_t n, int *nb)
{
	char	*hexa;

	hexa = "0123456789ABCDEF";
	if (n >= 16)
	{
		ft_putnbr_pointer(n / 16, nb);
		ft_putnbr_pointer(n % 16, nb);
	}
	else
		ft_putchar(hexa[n], nb);
}

void	ft_putunbr(unsigned int n, int *nb)
{
	if (n >= 10)
	{
		ft_putunbr(n / 10, nb);
		ft_putunbr(n % 10, nb);
	}
	else
		ft_putchar(n + '0', nb);
}

void	ft_putnbr(long n, int *nb)
{
	if (n < 0)
	{
		ft_putchar('-', nb);
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10, nb);
		ft_putnbr(n % 10, nb);
	}
	else
		ft_putchar(n + '0', nb);
}

void	ft_putnbr_size_t(size_t n, int *nb)
{
	if (n >= 10)
	{
		ft_putnbr_size_t(n / 10, nb);
		ft_putnbr_size_t(n % 10, nb);
	}
	else
		ft_putchar(n + '0', nb);
}
