/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:23:55 by dagredan          #+#    #+#             */
/*   Updated: 2025/01/01 21:35:47 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Writes an integer to the specified file descriptor.
 */
void	ft_putnbr_fd(int n, int fd)
{
	char	digit;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		ft_putnbr_fd(-n, fd);
		return ;
	}
	if (n < 10)
	{
		digit = n + '0';
		write(fd, &digit, 1);
		return ;
	}
	ft_putnbr_fd(n / 10, fd);
	digit = (n % 10) + '0';
	write(fd, &digit, 1);
	return ;
}
