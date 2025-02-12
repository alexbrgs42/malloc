/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:19:57 by pbourgeo          #+#    #+#             */
/*   Updated: 2023/11/02 14:11:20 by pbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*l1;

	if (lst != NULL && del != NULL)
	{
		while (*lst != NULL)
		{
			l1 = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = l1;
		}
	}
}
