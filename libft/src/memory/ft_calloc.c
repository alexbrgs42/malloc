/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:09:30 by pbourgeo          #+#    #+#             */
/*   Updated: 2023/11/02 15:21:18 by pbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*str;
	size_t	i;

	i = 0;
	if (nmemb * size == 0)
	{
		str = malloc(sizeof(char));
		if (str != NULL)
			str[0] = '\0';
		return (str);
	}
	if (nmemb * size < 0 || nmemb * size < nmemb || nmemb * size < size)
		return (NULL);
	str = malloc(nmemb * size);
	if (str == NULL)
		return (NULL);
	while (i < nmemb * size)
		str[i++] = 0;
	return ((void *)str);
}
