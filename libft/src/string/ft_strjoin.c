/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:15:22 by pbourgeo          #+#    #+#             */
/*   Updated: 2023/11/02 14:15:27 by pbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	__strjoin_bis(char *dest, char const *s1, int *i, int ls1)
{
	while (++(*i) < ls1)
		dest[*i] = s1[*i];
}

char	*ft_strjoin(char const *str1, char const *str2)
{
	int		size_str1;
	int		size_str2;
	int		i;
	char	*dest;

	size_str1 = 0;
	size_str2 = 0;
	i = -1;
	if (str1 == NULL && str2 == NULL)
		return (NULL);
	while (str1 != NULL && str1[size_str1])
		size_str1++;
	while (str2 != NULL && str2[size_str2])
		size_str2++;
	dest = malloc((size_str1 + size_str2 + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	__strjoin_bis(dest, str1, &i, size_str1);
	while (i < size_str1 + size_str2)
	{
		dest[i] = str2[i - size_str1];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
