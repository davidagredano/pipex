/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:59:30 by dagredan          #+#    #+#             */
/*   Updated: 2025/01/02 21:47:21 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Iterates through a list, applying the given function
 * to the content of each element.
 * Creates a new list with the results of the function applied to each element.
 * Returns the new list, or NULL if memory allocation fails.
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_node;
	void	*new_content;

	if (!f || !del)
		return (NULL);
	new_lst = NULL;
	while (lst)
	{
		new_content = f(lst->content);
		if (new_content == NULL)
			break ;
		new_node = ft_lstnew(new_content);
		if (new_node == NULL)
			break ;
		ft_lstadd_back(&new_lst, new_node);
		lst = lst->next;
	}
	if (lst)
	{
		free(new_content);
		ft_lstclear(&new_lst, del);
		return (NULL);
	}
	return (new_lst);
}
