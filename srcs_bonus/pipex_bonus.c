/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:53:21 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/11 16:25:35 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"
#include "../libft/libft.h"

void	pipex_free(t_pipex *data)
{
	if (!data)
		return ;
	if (data->processes)
		processes_free(data->processes);
	if (data->pipes)
		pipes_free(data->pipes);
	if (data->heredoc)
		heredoc_free(data->heredoc);
	free(data);
}

int	pipex_cleanup(t_pipex *data)
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
	if (wait_ret == -1 || close_ret == -1)
		exit(EXIT_FAILURE);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

int	pipex_perror_cleanup_exit(char *message, t_pipex *data, int status)
{
	perror(message);
	pipex_cleanup(data);
	exit(status);
}

t_pipex	*pipex_create(int argc, char *argv[], char *envp[])
{
	t_pipex	*data;

	data = (t_pipex *) ft_calloc(1, sizeof(t_pipex));
	if (!data)
		free_perror_exit(data, "pipex_create", EXIT_FAILURE);
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		data->heredoc_enabled = 1;
		data->heredoc = heredoc_create();
		if (!data->heredoc)
			free_perror_exit(data, "heredoc_create", EXIT_FAILURE);
	}
	data->processes_count = argc - 3 - data->heredoc_enabled;
	data->processes = processes_create(data->processes_count);
	if (!data->processes)
		free_perror_exit(data, "processes_create", EXIT_FAILURE);
	data->pipes_count = data->processes_count - 1;
	data->pipes = pipes_create(data->pipes_count);
	if (!data->pipes)
		free_perror_exit(data, "pipes_create", EXIT_FAILURE);
	data->envp = envp;
	if (data->heredoc_enabled)
	{
		if (heredoc_init(data->heredoc, argv) == -1)
			free_perror_exit(data, "heredoc_init", EXIT_FAILURE);
	}
	processes_init(data, argc, argv);
	return (data);
}
