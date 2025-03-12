/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:48:22 by dagredan          #+#    #+#             */
/*   Updated: 2025/01/18 18:50:43 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Writes a single character to the standard output.
 * Return the number of characters printed, or -1 on error.
 */
int	ft_putchar(char c)
{
	return ((int) write(STDOUT_FILENO, &c, 1));
}
