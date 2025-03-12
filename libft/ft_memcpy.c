/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:49:25 by dagredan          #+#    #+#             */
/*   Updated: 2025/01/01 21:13:50 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Copies bytes from source to destination memory area.
 * Returns a pointer to the destination area.
 * Warning: doesn't handle overlapping memory areas correctly.
 * Use memmove when memory regions might overlap.
 */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest_unsigned_char;
	unsigned char	*src_unsigned_char;

	i = 0;
	dest_unsigned_char = (unsigned char *) dest;
	src_unsigned_char = (unsigned char *) src;
	while (i < n)
	{
		dest_unsigned_char[i] = src_unsigned_char[i];
		i++;
	}
	return (dest);
}
