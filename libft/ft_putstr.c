/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 09:33:53 by dagredan          #+#    #+#             */
/*   Updated: 2025/01/18 18:51:30 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Writes a string to the standard output, 
 * without its terminating null byte ('\0').
 * Return the number of characters printed, or -1 on error.
 */
int	ft_putstr(const char *s)
{
	if (!s)
		return (-1);
	return ((int) write(STDOUT_FILENO, s, ft_strlen(s)));
}
