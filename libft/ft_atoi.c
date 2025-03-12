/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:10:09 by dagredan          #+#    #+#             */
/*   Updated: 2025/01/01 21:28:39 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Converts a string to an integer, handling leading white space and sign.
 * Stops conversion at the first non-digit character.
 * Returns the resulting integer.
 */
int	ft_atoi(const char *nptr)
{
	int		accumulated;
	int		sign;
	size_t	i;

	sign = 1;
	i = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	accumulated = 0;
	while (ft_isdigit(nptr[i]))
	{
		accumulated = accumulated * 10 + (nptr[i] - '0');
		i++;
	}
	return (sign * accumulated);
}
