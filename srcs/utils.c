/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:12:33 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/03 17:15:50 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_strs(char **strs)
{
	char	**ptr;

	ptr = strs;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(strs);
}
