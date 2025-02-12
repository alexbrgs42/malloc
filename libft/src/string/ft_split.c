/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:14:14 by pbourgeo          #+#    #+#             */
/*   Updated: 2023/11/02 14:14:22 by pbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	__nb(char const *str, char sep)
{
	int	i;
	int	size_str;

	i = 0;
	size_str = 0;
	while (str[size_str] != '\0')
	{
		if (str[size_str] != sep)
		{
			i++;
			while (str[size_str] != '\0' && str[size_str] != sep)
				size_str++;
		}
		else
			size_str++;
	}
	return (i);
}

static char	*__subtab(char const *str, char sep, int *size_str)
{
	int		i;
	char	*sub_dest;

	i = 0;
	while (str[i] != '\0' && str[i] != sep)
		i++;
	sub_dest = malloc((i + 1) * sizeof(char));
	if (sub_dest == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != sep)
	{
		sub_dest[i] = str[i];
		i++;
	}
	*size_str += i;
	sub_dest[i] = '\0';
	return (sub_dest);
}

static char	**__free(char **dest, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		free(dest[i]);
	free(dest);
	return (NULL);
}

char	**ft_split(char const *str, char sep)
{
	int		i;
	int		size_str;
	char	**dest;

	size_str = 0;
	i = 0;
	if (str == NULL)
		return (NULL);
	dest = malloc((__nb(str, sep) + 1) * sizeof(char *));
	if (dest == NULL)
		return (NULL);
	while (str[size_str] != '\0')
	{
		if (str[size_str] == sep)
			size_str++;
		else
		{
			dest[i++] = __subtab(&str[size_str], sep, &size_str);
			if (dest == NULL)
				return (__free(dest, i));
		}
	}
	dest[i] = NULL;
	return (dest);
}
