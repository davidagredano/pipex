/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 16:45:23 by dagredan          #+#    #+#             */
/*   Updated: 2025/01/01 22:01:23 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Duplicates a string by allocating enough memory and copying the content.
 * Returns a pointer to the new string, or NULL if allocation fails.
 */
char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	size;

	size = ft_strlen(s) + 1;
	dup = (char *) ft_calloc(size, sizeof(char));
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s, size);
	return (dup);
}
