/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:45:33 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/10 20:28:11 by dagredan         ###   ########.fr       */
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

void	processes_init(t_pipex *data, int argc, char *argv[])
{
	int		i;
	t_proc	*process;

	i = 0;
	while (i < data->processes_count)
	{
		process = data->processes[i];
		if (i > 0)
			process->pipe_read_fd = data->pipes[i - 1][0];
		if (i < data->processes_count - 1)
			process->pipe_write_fd = data->pipes[i][1];
		if (i == 0)
			process->infile = argv[1];
		if (i == data->processes_count - 1)
			process->outfile = argv[argc - 1];
		process->cmd_str = argv[i + 2];
		i++;
	}
}

t_proc	**processes_create(int count)
{
	t_proc	**processes;
	int		i;

	processes = (t_proc **) ft_calloc(count + 1, sizeof(t_proc *));
	if (!processes)
		return (NULL);
	i = 0;
	while (i < count)
	{
		processes[i] = (t_proc *) ft_calloc(1, sizeof(t_proc));
		if (!processes)
		{
			processes_free(processes);
			return (NULL);
		}
		processes[i]->pipe_read_fd = -1;
		processes[i]->pipe_write_fd = -1;
		i++;
	}
	return (processes);
}
