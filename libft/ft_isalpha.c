/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:15:38 by dagredan          #+#    #+#             */
/*   Updated: 2025/01/01 21:08:42 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Checks if a character is alphabetic (A-Z or a-z).
 * Returns 1 if character is alphabetic, 0 otherwise.
 */
int	ft_isalpha(int c)
{
	return (ft_isupper(c) || ft_islower(c));
}
