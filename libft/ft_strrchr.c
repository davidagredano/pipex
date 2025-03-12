/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 18:09:52 by dagredan          #+#    #+#             */
/*   Updated: 2025/01/01 21:18:26 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Finds the last occurrence of a character in a string.
 * Returns a pointer to the last occurrence of the character,
 * or NULL if not found.
 */
char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	if (s[i] == '\0' && (char) c == '\0')
		return ((char *) &s[i]);
	while (i > 0)
	{
		i--;
		if (s[i] == (char) c)
			return ((char *) &s[i]);
	}
	return (NULL);
}
