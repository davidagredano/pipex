/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:22:36 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/19 17:44:44 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Calculates the length of the initial segment of a string
 * that does not contain any characters from a specified set.
 * Returns the number of characters before the first occurrence
 * of any character from the specified set.
 */
size_t	ft_strcspn(const char *str, const char *reject)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_strchr(reject, str[i]))
			break ;
		i++;
	}
	return (i);
}
