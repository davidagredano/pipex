/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:12:33 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/20 21:12:58 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../libft/libft.h"

int	parent_cleanup(t_pipex *data)
{
	int	status;
	int	close_ret;
	int	wait_ret;

	close_ret = pipes_destroy(data);
	if (close_ret == -1)
		perror("pipes_destroy");
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

void	parent_cleanup_exit(t_pipex *data, char *message)
{
	perror(message);
	if (pipes_destroy(data) == -1)
		perror("pipes_destroy");
	if (processes_wait(data, NULL) == -1)
		perror("processes_wait");
	pipex_free(data);
	exit(EXIT_FAILURE);
}

void	child_cleanup_exit(t_pipex *data, char *error_message, int exit_status)
{
	if (exit_status == EXIT_COMMAND_NOT_FOUND)
	{
		ft_putstr_fd(error_message, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
	else
		perror(error_message);
	if (pipes_destroy(data) == -1)
		perror("pipes_destroy");
	pipex_free(data);
	exit(exit_status);
}
