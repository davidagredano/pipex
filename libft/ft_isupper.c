/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 21:20:41 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/12 21:20:44 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Checks if a character is an uppercase letter (A-Z).
 * Returns 1 if uppercase, 0 otherwise.
 */
int	ft_isupper(int c)
{
	return (c >= 'A' && c <= 'Z');
}
