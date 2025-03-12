/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 18:49:24 by dagredan          #+#    #+#             */
/*   Updated: 2025/01/03 11:47:21 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

/**
 * Concatenates two strings into a new string.
 * Returns the newly allocated string containing s1 followed by s2,
 * or NULL if allocation fails.
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	int		memsize;

	if (!s1 || !s2)
		return (NULL);
	memsize = ft_strlen(s1) + ft_strlen(s2) + 1;
	newstr = (char *) ft_calloc(memsize, sizeof(char));
	if (!newstr)
		return (NULL);
	ft_strlcpy(newstr, s1, memsize);
	ft_strlcat(newstr, s2, memsize);
	return (newstr);
}
