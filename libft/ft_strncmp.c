/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:58:44 by dagredan          #+#    #+#             */
/*   Updated: 2025/01/01 21:19:01 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Compares up to n characters of two strings.
 * The comparison is done using unsigned characters.
 * Returns 0 if the strings are equal, a positive or negative number otherwise.
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n - 1 && s1[i] == s2[i] && s1[i] != '\0')
		i++;
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}
