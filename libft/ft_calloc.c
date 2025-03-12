/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:21:27 by dagredan          #+#    #+#             */
/*   Updated: 2025/01/01 22:01:51 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Allocates memory for an array of n members of size bytes each,
 * and initializes all bytes to zero.
 * Includes protection against integer overflow in nmemb * size.
 * Returns a pointer to the allocated memory, or NULL if allocation fails.
 */
void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total_size;
	void	*mem;

	total_size = nmemb * size;
	if (total_size > 0 && nmemb != total_size / size)
		return (NULL);
	mem = malloc(total_size);
	if (!mem)
		return (NULL);
	ft_memset(mem, 0, total_size);
	return (mem);
}
