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

int	cleanup(t_pipex *data)
{
	int	status;
	int	close_ret;
	int	wait_ret;

	close_ret = pipes_close(data->pipes);
	if (close_ret == -1)
		perror("pipes_close");
	wait_ret = processes_wait(data, &status);
	if (wait_ret == -1)
		perror("processes_wait");
	pipex_free(data);
	if (close_ret == -1 || wait_ret == -1)
		exit(EXIT_FAILURE);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

void	cleanup_exit(t_pipex *data, char *message, int status)
{
	perror(message);
	cleanup(data);
	exit(status);
}
