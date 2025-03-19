/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:21:47 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/19 17:44:32 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Calculates the length of the initial segment of a string
 * that consists entirely of characters from a specified set.
 * Returns the length of the initial segment containing
 * only these characters.
 */
size_t	ft_strspn(const char *str, const char *accept)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_strchr(accept, str[i]))
			break ;
		i++;
	}
	return (i);
}
