/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:44:22 by dagredan          #+#    #+#             */
/*   Updated: 2025/01/03 11:28:14 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Extracts a substring from a string starting at index start and of length len.
 * If start is beyond the length of s, returns an empty string.
 * Returns the allocated substring, or NULL if allocation fails.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	strlen;
	size_t	size;

	if (!s)
		return (NULL);
	strlen = ft_strlen(s);
	if (start >= strlen)
		size = 1;
	else if (strlen - start < len)
		size = strlen - start + 1;
	else
		size = len + 1;
	substr = (char *) ft_calloc(size, sizeof(char));
	if (!substr)
		return (NULL);
	if (size > 1)
		ft_strlcpy(substr, s + start, size);
	return (substr);
}
