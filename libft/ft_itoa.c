/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:32:20 by dagredan          #+#    #+#             */
/*   Updated: 2025/01/11 18:15:46 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nlen(int n)
{
	if (n / 10 == 0)
		return (1);
	return (1 + ft_nlen(n / 10));
}

static int	ft_neg_sign(int n)
{
	return (n < 0);
}

/**
 * Converts an integer to a string representation.
 * Allocates memory for the resulting string and returns it,
 * or NULL if allocation fails.
 */
char	*ft_itoa(int n)
{
	char	*str;
	int		neg_sign;
	int		i;

	neg_sign = ft_neg_sign(n);
	str = (char *) ft_calloc((neg_sign + ft_nlen(n) + 1), sizeof(char));
	if (!str)
		return (NULL);
	if (n == -2147483648)
	{
		ft_strlcpy(str, "-2147483648", 12);
		return (str);
	}
	if (neg_sign)
		n = -n;
	i = neg_sign + ft_nlen(n);
	while (--i >= 0)
	{
		str[i] = (n % 10) + '0';
		n = n / 10;
	}
	if (neg_sign)
		str[0] = '-';
	return (str);
}
