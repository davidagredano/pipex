/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 11:25:14 by dagredan          #+#    #+#             */
/*   Updated: 2025/01/01 21:14:23 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Copies bytes from source to destination.
 * Returns a pointer to the destination area.
 * Safely handles overlapping memory.
 */
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_unsigned_char;
	unsigned char	*src_unsigned_char;
	size_t			i;

	dest_unsigned_char = (unsigned char *) dest;
	src_unsigned_char = (unsigned char *) src;
	if (src < dest)
	{
		i = n;
		while (i > 0)
		{
			i--;
			dest_unsigned_char[i] = src_unsigned_char[i];
		}
	}
	else if (src > dest)
	{
		i = 0;
		while (i < n)
		{
			dest_unsigned_char[i] = src_unsigned_char[i];
			i++;
		}
	}
	return (dest);
}
