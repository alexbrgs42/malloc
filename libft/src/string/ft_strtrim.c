/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:17:18 by pbourgeo          #+#    #+#             */
/*   Updated: 2023/11/02 14:17:21 by pbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	__totrim(char c, char const *set)
{
	int	i;

	i = 0;
	while (set != NULL && set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *str, char const *set)
{
	int		i;
	int		start;
	int		end;
	char	*dest;

	if (str == NULL)
		return (NULL);
	i = 0;
	start = 0;
	end = ft_strlen((char *)str) - 1;
	while (str[start] != '\0' && __totrim(str[start], set) != 0)
		start++;
	while (__totrim(str[end], set) && end > start)
		end--;
	dest = malloc((end - start + 2) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (start <= end)
		dest[i++] = str[start++];
	dest[i] = '\0';
	return (dest);
}
