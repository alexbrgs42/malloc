/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:12:30 by pbourgeo          #+#    #+#             */
/*   Updated: 2023/11/09 12:58:34 by pbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *pointer, int c, size_t n)
{
	size_t			i;
	unsigned char	*casted_ptr;
	unsigned char	casted_c;

	i = 0;
	casted_ptr = (unsigned char *)pointer;
	casted_c = (unsigned char)c;
	if (n == 0)
		return (NULL);
	while (i < n)
	{
		if (casted_ptr[i] == casted_c)
			return (casted_ptr + i);
		i++;
	}
	return (NULL);
}
