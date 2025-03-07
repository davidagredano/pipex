/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:12:33 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/07 17:28:20 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	cleanup(int pipe[2], pid_t pid[2])
{
	int	status;

	close(pipe[0]);
	close(pipe[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], &status, 0);
	return (status);
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
