/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:12:41 by pbourgeo          #+#    #+#             */
/*   Updated: 2023/11/02 15:31:41 by pbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t n)
{
	size_t			i;
	unsigned char	*casted_ptr1;
	unsigned char	*casted_ptr2;

	i = 0;
	if (n == 0)
		return (0);
	casted_ptr1 = (unsigned char *)ptr1;
	casted_ptr2 = (unsigned char *)ptr2;
	while (i < n - 1 && casted_ptr1[i] == casted_ptr2[i])
		i++;
	return (casted_ptr1[i] - casted_ptr2[i]);
}
