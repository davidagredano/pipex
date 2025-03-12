/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 18:09:52 by dagredan          #+#    #+#             */
/*   Updated: 2025/01/01 21:43:22 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Finds the first occurrence of a character in a string.
 * Returns a pointer to the first occurrence of the character,
 * or NULL if not found.
 */
char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == '\0' && (char) c == '\0')
		return ((char *) &s[i]);
	return (NULL);
}
