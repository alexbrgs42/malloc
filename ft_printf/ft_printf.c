/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:38:39 by pbourgeo          #+#    #+#             */
/*   Updated: 2023/11/08 22:31:09 by pbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c, int *nb)
{
	write(1, &c, 1);
	(*nb)++;
}

void	ft_putstr(char *str, int *nb)
{
	int	i;

	i = 0;
	if (!str)
		ft_putstr("(null)", nb);
	else
	{
		while (str && str[i])
		{
			write(1, &str[i], 1);
			i++;
			(*nb)++;
		}
	}
}

void	ft_putnbr_hexa(unsigned int n, unsigned int base, int *nb, int upper)
{
	char	*base_low;
	char	*base_up;

	base_low = "0123456789abcdef";
	base_up = "0123456789ABCDEF";
	if (n >= base)
	{
		ft_putnbr_hexa(n / base, base, nb, upper);
		ft_putnbr_hexa(n % base, base, nb, upper);
	}
	else
	{
		if (upper)
			ft_putchar(base_up[n], nb);
		else
			ft_putchar(base_low[n], nb);
	}
}

void	ft_printf_bis(va_list ap, int *nb, const char *str, int *i)
{
	if (str[*i] == '%' && str[*i + 1] == 'c')
		ft_putchar((char)va_arg(ap, int), nb);
	else if (str[*i] == '%' && str[*i + 1] == 's')
		ft_putstr(va_arg(ap, char *), nb);
	else if (str[*i] == '%' && str[*i + 1] == 'p')
		ft_put_pointer(va_arg(ap, void *), nb);
	else if (str[*i] == '%' && str[*i + 1] == 'd')
		ft_putnbr((long)va_arg(ap, int), nb);
	else if (str[*i] == '%' && str[*i + 1] == 'i')
		ft_putnbr((long)va_arg(ap, int), nb);
	else if (str[*i] == '%' && str[*i + 1] == 'u')
		ft_putunbr((unsigned)va_arg(ap, unsigned int), nb);
	else if (str[*i] == '%' && str[*i + 1] == 'x')
		ft_putnbr_hexa((unsigned int)va_arg(ap, int), 16, nb, 0);
	else if (str[*i] == '%' && str[*i + 1] == 'X')
		ft_putnbr_hexa((unsigned int)va_arg(ap, int), 16, nb, 1);
	else if (str[*i] == '%' && str[*i + 1] == '%')
		ft_putchar('%', nb);
	else
	{
		ft_putchar(str[*i], nb);
		(*i)--;
	}
	*i += 2;
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	if (!str)
		return (-1);
	va_start(ap, str);
	while (str[i])
		ft_printf_bis(ap, &nb, str, &i);
	va_end(ap);
	return (nb);
}
