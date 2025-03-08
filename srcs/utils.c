/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:12:33 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/08 12:52:35 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	perror_exit(char *message, int status)
{
	perror(message);
	exit(status);
}

int	cleanup(int pipe[2])
{
	int	last_process_status;
	int	close_ret_val[2];
	int	wait_ret_val[2];

	close_ret_val[0] = close(pipe[0]);
	close_ret_val[1] = close(pipe[1]);
	wait_ret_val[0] = wait(NULL);
	wait_ret_val[1] = wait(&last_process_status);
	if (wait_ret_val[0] == -1 || wait_ret_val[1] == -1)
	{
		perror("wait");
		exit(EXIT_FAILURE);
	}
	else if (close_ret_val[0] == -1 || close_ret_val[1] == -1)
	{
		perror("close");
		exit(EXIT_FAILURE);
	}
	return (last_process_status);
}

void	cleanup_partial(int pipe[2])
{
	int	close_ret_val[2];
	int	wait_ret_val;

	close_ret_val[0] = close(pipe[0]);
	close_ret_val[1] = close(pipe[1]);
	wait_ret_val = wait(NULL);
	if (wait_ret_val == -1)
	{
		perror("wait");
		exit(EXIT_FAILURE);
	}
	else if (close_ret_val[0] == -1 || close_ret_val[1] == -1)
	{
		perror("close");
		exit(EXIT_FAILURE);
	}
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
