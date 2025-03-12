/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 12:17:19 by dagredan          #+#    #+#             */
/*   Updated: 2025/01/02 21:46:53 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Deletes and frees the list element pointed to,
 * as well as all following elements.
 * The function uses the provided del function
 * to free the content of each element.
 */
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;

	if (!del)
		return ;
	while (*lst)
	{
		next = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = next;
	}
}
