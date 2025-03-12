/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 19:14:58 by dagredan          #+#    #+#             */
/*   Updated: 2025/01/02 21:47:27 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Creates a new list element with the given content.
 * Allocates memory for the element and sets its content and next pointer.
 * Returns a pointer to the new element, or NULL if allocation fails.
 */
t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = (t_list *) malloc(1 * sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}
