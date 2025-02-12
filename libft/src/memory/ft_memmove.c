/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:13:07 by pbourgeo          #+#    #+#             */
/*   Updated: 2023/11/02 14:13:09 by pbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*casted_dest;
	unsigned char	*casted_src;

	casted_dest = (unsigned char *)dest;
	casted_src = (unsigned char *)src;
	if (n != 0)
	{
		if (casted_dest > casted_src)
		{
			i = n;
			while (i-- > 0)
				casted_dest[i] = casted_src[i];
		}
		else if (casted_dest < casted_src)
		{
			i = 0;
			while (i < n)
			{
				casted_dest[i] = casted_src[i];
				i++;
			}
		}
	}
	return (dest);
}
