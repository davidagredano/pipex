/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:50:30 by dagredan          #+#    #+#             */
/*   Updated: 2025/01/01 21:11:18 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Checks if a character is a decimal digit (0-9).
 * Returns 1 if character is a digit, 0 otherwise.
 */
int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
