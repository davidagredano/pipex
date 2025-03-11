/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:12:33 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/10 20:31:41 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	free_perror_exit(t_pipex *data, char *message, int status)
{
	pipex_free(data);
	perror(message);
	exit(status);
}

void	free_exit(t_pipex *data, int status)
{
	pipex_free(data);
	exit(status);
}

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
