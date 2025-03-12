/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:40:54 by dagredan          #+#    #+#             */
/*   Updated: 2025/01/01 21:13:08 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Fills a block of memory with a specified byte value.
 * Returns a pointer to the memory area.
 */
void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s_unsigned_char;

	s_unsigned_char = s;
	i = 0;
	while (i < n)
	{
		s_unsigned_char[i] = c;
		i++;
	}
	return (s);
}
