/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:37:25 by dagredan          #+#    #+#             */
/*   Updated: 2025/01/01 21:15:55 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Appends src to the end of dest, ensuring NUL-termination within size bytes.
 * Returns the total length of the string it tried to create (dest + src).
 * Note that if no NUL is found traversing dest, returns (size + src).
 */
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;

	if (size == 0)
		return (ft_strlen(src));
	dst_len = ft_strlen(dst);
	if (size <= dst_len)
		return (size + ft_strlen(src));
	src_len = ft_strlcpy(dst + dst_len, src, size - dst_len);
	return (dst_len + src_len);
}
