/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:56:49 by dagredan          #+#    #+#             */
/*   Updated: 2025/01/02 22:46:12 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Locates the first occurrence of a byte in a memory area.
 * Returns a pointer to the matching byte or NULL if not found.
 * All bytes are interpreted as unsigned char.
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_unsigned_char;
	size_t			i;

	s_unsigned_char = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (s_unsigned_char[i] == (unsigned char) c)
			return ((void *) s + i);
		i++;
	}
	return (NULL);
}
