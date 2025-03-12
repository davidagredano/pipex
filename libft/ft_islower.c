/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_islower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 21:20:25 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/12 21:20:28 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Checks if a character is a lowercase letter (a-z).
 * Returns 1 if lowercase, 0 otherwise.
 */
int	ft_islower(int c)
{
	return (c >= 'a' && c <= 'z');
}
