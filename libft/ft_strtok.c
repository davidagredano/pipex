/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:18:22 by dagredan          #+#    #+#             */
/*   Updated: 2025/02/12 21:16:39 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Splits a string into tokens using specified delimiter characters.
 * First call uses input string, for subsequent calls use NULL.
 * Modifies the original string by replacing delimiters with '\0'.
 * Returns pointer to the next token, or NULL when no tokens remain.
 */
char	*ft_strtok(char *str, const char *delim)
{
	static char	*old_str;
	char		*token;

	if (!str)
		str = old_str;
	if (!str)
		return (NULL);
	while (*str != '\0' && ft_strchr(delim, *str))
		str++;
	if (*str == '\0')
	{
		old_str = NULL;
		return (NULL);
	}
	token = str;
	while (*str != '\0' && !ft_strchr(delim, *str))
		str++;
	if (*str == '\0')
		old_str = NULL;
	else
	{
		*str = '\0';
		old_str = str + 1;
	}
	return (token);
}
