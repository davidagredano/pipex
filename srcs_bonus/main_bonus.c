/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:53:33 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/11 14:54:19 by dagredan         ###   ########.fr       */
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

static t_pipex	*pipex_create(int argc, char *argv[], char *envp[])
{
	t_pipex	*data;

	data = (t_pipex *) ft_calloc(1, sizeof(t_pipex));
	if (!data)
		process_perror_free_exit("pipex_create", data, EXIT_FAILURE);
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		data->heredoc_enabled = 1;
		data->heredoc = heredoc_create();
		if (!data->heredoc)
			process_perror_free_exit("heredoc_create", data, EXIT_FAILURE);
	}
	data->processes_count = argc - 3 - data->heredoc_enabled;
	data->processes = processes_create(data->processes_count);
	if (!data->processes)
		process_perror_free_exit("processes_create", data, EXIT_FAILURE);
	data->pipes_count = data->processes_count - 1;
	data->pipes = pipes_create(data->pipes_count);
	if (!data->pipes)
		process_perror_free_exit("pipes_create", data, EXIT_FAILURE);
	data->envp = envp;
	if (data->heredoc_enabled)
	{
		if (heredoc_init(data->heredoc, argv) == -1)
			process_perror_free_exit("heredoc_init", data, EXIT_FAILURE);
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
	pid_t	pid;
	int		i;

	pipex_ensure_proper_usage(argc, argv);
	data = pipex_create(argc, argv, envp);
	i = 0;
	while (i < data->processes_count)
	{
		pid = fork();
		if (pid == -1)
			pipex_perror_cleanup_exit("fork", data, EXIT_FAILURE);
		else if (pid == 0)
		{
			process_redirect_stdin(data, data->processes[i]);
			process_redirect_stdout(data, data->processes[i]);
			if (pipes_close(data->pipes) == -1)
				process_perror_free_exit("pipes_close", data, EXIT_FAILURE);
			process_execute(data, command_create(data, data->processes[i]));
		}
		data->processes_active++;
		i++;
	}
	return (pipex_cleanup(data));
}
