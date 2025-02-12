/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:10:53 by pbourgeo          #+#    #+#             */
/*   Updated: 2023/11/02 14:10:56 by pbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lst2;

	if (lst && new)
	{
		lst2 = *lst;
		if (!(*lst))
			*lst = new;
		else
		{
			while (lst2->next)
				lst2 = lst2->next;
			lst2->next = new;
		}
	}
}
