/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:53:33 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/14 10:01:45 by dagredan         ###   ########.fr       */
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
	pipes_destroy(data);
	if (data->heredoc_enabled)
		heredoc_free(data->heredoc);
	free(data);
}

static t_pipex	*pipex_create(int argc, char *argv[], char *envp[])
{
	t_pipex	*data;

	data = (t_pipex *) ft_calloc(1, sizeof(t_pipex));
	if (!data)
		parent_cleanup_exit(data, "pipex_create");
	heredoc_create(data, ft_strcmp(argv[1], "here_doc") == 0);
	processes_create(data, argc - 3 - data->heredoc_enabled);
	pipes_create(data, data->processes_count - 1);
	data->envp = envp;
	if (data->heredoc_enabled)
	{
		heredoc_init(data, argv);
		heredoc_read_stdin(data);
	}
	processes_init(data, argc, argv);
	return (data);
}

static void	pipex_ensure_proper_usage(int argc, char *argv[])
{
	int	is_here_doc;

	is_here_doc = (argv[1] && ft_strcmp(argv[1], "here_doc") == 0);
	if (!is_here_doc && argc < 5)
	{
		ft_putstr_fd("Error: Not enough arguments\n", 2);
		exit(EXIT_FAILURE);
	}
	if (is_here_doc && argc < 6)
	{
		ft_putstr_fd("Error: Not enough arguments for here_doc\n", 2);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	*data;
	int		i;

	pipex_ensure_proper_usage(argc, argv);
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
			process_execute(data, command_create(data, data->processes[i]));
		}
		i++;
	}
	return (parent_cleanup(data));
}
