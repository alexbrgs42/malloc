/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:10:35 by pbourgeo          #+#    #+#             */
/*   Updated: 2023/11/02 14:10:40 by pbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	__ft_putnbr(long num, char *dest, int *i)
{
	if (num < 0)
	{
		num = -num;
		dest[(*i)++] = '-';
	}
	if (num >= 10)
	{
		__ft_putnbr(num / 10, dest, i);
		__ft_putnbr(num % 10, dest, i);
	}
	else
		dest[(*i)++] = num + '0';
}

static int	__sizeof_num(int num)
{
	int	size_num;

	size_num = 0;
	if (num < 0)
		size_num++;
	if (num == 0)
		return (2);
	while (num != 0)
	{
		num = num / 10;
		size_num++;
	}
	return (size_num + 1);
}

char	*ft_itoa(int num)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(__sizeof_num(num) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	__ft_putnbr((long)num, dest, &i);
	dest[i] = '\0';
	return (dest);
}
