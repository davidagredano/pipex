/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:53:33 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/18 22:06:22 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../libft/libft.h"

void	pipex_free(t_pipex *data)
{
	if (!data)
		return ;
	if (data->path_dirs)
		path_dirs_free(data->path_dirs);
	if (data->processes)
		processes_free(data->processes);
	pipes_destroy(data);
	free(data);
}

static t_pipex	*pipex_create(int argc, char *argv[], char *envp[])
{
	t_pipex	*data;

	data = (t_pipex *) ft_calloc(1, sizeof(t_pipex));
	if (!data)
		parent_cleanup_exit(data, "pipex_create");
	data->envp = envp;
	path_dirs_create(data, envp);
	processes_create(data, argc - 3);
	pipes_create(data, data->processes_count - 1);
	processes_init(data, argc, argv);
	return (data);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	*data;
	int		i;

	if (argc != 5)
		exit(EXIT_FAILURE);
	data = pipex_create(argc, argv, envp);
	i = 0;
	while (i < data->processes_count)
	{
		data->processes[i]->pid = fork();
		if (data->processes[i]->pid == -1)
			parent_cleanup_exit(data, "fork");
		else if (data->processes[i]->pid == 0)
		{
			process_redirect_stdin(data, data->processes[i]);
			process_redirect_stdout(data, data->processes[i]);
			if (pipes_destroy(data) == -1)
				child_cleanup_exit(data, "pipes_destroy", EXIT_FAILURE);
			command_create(data, data->processes[i]);
			process_execute(data, data->processes[i]);
		}
		i++;
	}
	return (parent_cleanup(data));
}
