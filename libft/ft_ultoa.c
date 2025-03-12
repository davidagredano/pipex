/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 12:43:55 by dagredan          #+#    #+#             */
/*   Updated: 2025/01/12 13:50:37 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nlen(unsigned long n, int radix)
{
	if (n / radix == 0)
		return (1);
	return (1 + ft_nlen(n / radix, radix));
}

/**
 * Converts an unsigned long to a string representation (using lowercase).
 * Allocates memory for the resulting string and returns it,
 * or NULL if allocation fails.
 */
char	*ft_ultoa(unsigned long n, int radix)
{
	char	*str;
	int		i;

	if (radix < 2 || radix > 36)
		return (NULL);
	str = (char *) ft_calloc(ft_nlen(n, radix) + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = ft_nlen(n, radix);
	while (--i >= 0)
	{
		if (n % radix < 10)
			str[i] = (n % radix) + '0';
		else
			str[i] = ((n - 10) % radix) + 'a';
		n = n / radix;
	}
	return (str);
}
