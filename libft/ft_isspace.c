/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 21:11:50 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/12 21:11:52 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Checks if a character is a whitespace character.
 * Whitespace includes space, tab, newline, vertical tab,
 * form feed, and carriage return.
 * Returns 1 if the character is whitespace, 0 otherwise.
 */
int	ft_isspace(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}
