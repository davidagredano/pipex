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

void	strs_free(char **strs)
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

void	process_perror_free_exit(char *message, t_pipex *data, int status)
{
	perror(message);
	pipex_free(data);
	exit(status);
}

int	pipex_perror_cleanup_exit(char *message, t_pipex *data, int status)
{
	perror(message);
	pipex_cleanup(data);
	exit(status);
}
