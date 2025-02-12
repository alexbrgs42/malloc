/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:15:36 by pbourgeo          #+#    #+#             */
/*   Updated: 2023/11/02 14:15:39 by pbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	src_len;
	size_t	cur;

	if (size == 0)
		return ((size_t)ft_strlen((char *)src));
	src_len = ft_strlen(dest);
	cur = 0;
	if (size <= src_len)
		return (ft_strlen((char *)src) + size);
	while (src[cur] && (src_len + cur) < (size - 1))
	{
		dest[src_len + cur] = src[cur];
		cur++;
	}
	dest[src_len + cur] = 0;
	return (ft_strlen((char *)src) + src_len);
}
