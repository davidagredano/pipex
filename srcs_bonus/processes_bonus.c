/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:45:33 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/13 00:01:58 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"
#include "../libft/libft.h"

void	processes_free(t_proc **processes)
{
	t_proc	**ptr;

	ptr = processes;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(processes);
}

int	processes_wait(t_pipex *data, int *status)
{
	int	ret;

	ret = 0;
	if (data->processes_active == 0)
		return (ret);
	while (data->processes_active > 0)
	{
		if (wait(status) == -1)
			ret = -1;
		data->processes_active--;
	}
	return (ret);
}

void	processes_init(t_pipex *data, int argc, char *argv[])
{
	t_proc	*process;
	int		i;

	i = 0;
	while (i < data->processes_count)
	{
		process = data->processes[i];
		if (i > 0)
			process->pipe_read_fd = data->pipes[i - 1][0];
		if (i < data->processes_count - 1)
			process->pipe_write_fd = data->pipes[i][1];
		if (i == 0)
		{
			if (data->heredoc_enabled)
				process->infile = data->heredoc->filename;
			else
				process->infile = argv[1];
		}
		if (i == data->processes_count - 1)
			process->outfile = argv[argc - 1];
		process->command_str = argv[i + 2 + data->heredoc_enabled];
		i++;
	}
}

void	processes_create(t_pipex *data, int count)
{
	int	i;

	data->processes_count = count;
	data->processes = (t_proc **)ft_calloc(count + 1, sizeof(t_proc *));
	if (!data->processes)
		cleanup_exit(data, "processes_create", EXIT_FAILURE);
	i = 0;
	while (i < count)
	{
		data->processes[i] = (t_proc *)ft_calloc(1, sizeof(t_proc));
		if (!data->processes[i])
			cleanup_exit(data, "processes_create", EXIT_FAILURE);
		data->processes[i]->pipe_read_fd = -1;
		data->processes[i]->pipe_write_fd = -1;
		i++;
	}
}
