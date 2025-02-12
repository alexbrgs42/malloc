/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:14:50 by pbourgeo          #+#    #+#             */
/*   Updated: 2023/11/02 14:15:11 by pbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *str, void (*f)(unsigned int, char *))
{
	int	i;

	i = 0;
	if (str == NULL || f == NULL)
		return ;
	while (str[i] != '\0')
	{
		f(i, &str[i]);
		i++;
	}
}
