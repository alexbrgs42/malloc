/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:12:56 by pbourgeo          #+#    #+#             */
/*   Updated: 2023/11/02 14:13:00 by pbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	if (src == NULL && dest == NULL)
		return (NULL);
	while (n-- != 0)
		((char *)dest)[n] = ((char *)src)[n];
	return (dest);
}
