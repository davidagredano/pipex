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

static void	process_execute(t_pipex *data, t_cmd *command)
{
	if (execve(command->filename, command->argv, data->envp) == -1)
	{
		command_free(command);
		free_perror_exit(data, "execve", EXIT_FAILURE);
	}
}

static void	process_redirect_stdout(t_pipex *data, t_proc *process)
{
	int	fd;

	if (process->outfile)
	{
		if (data->heredoc_enabled)
			fd = open(process->outfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
		else
			fd = open(process->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd == -1)
			free_perror_exit(data, process->outfile, EXIT_FAILURE);
		if (dup2(fd, STDOUT_FILENO) == -1)
			free_perror_exit(data, "dup2", EXIT_FAILURE);
		if (close(fd) == -1)
			free_perror_exit(data, "close", EXIT_FAILURE);
	}
	else
	{
		if (dup2(process->pipe_write_fd, STDOUT_FILENO) == -1)
			free_perror_exit(data, "dup2", EXIT_FAILURE);
	}
}

static void	process_redirect_stdin(t_pipex *data, t_proc *process)
{
	int	fd;

	if (process->infile)
	{
		fd = open(process->infile, O_RDONLY);
		if (fd != -1 && data->heredoc_enabled && unlink(process->infile) == -1)
			free_perror_exit(data, "unlink", EXIT_FAILURE);
		if (fd == -1)
		{
			perror(process->infile);
			fd = open("/dev/null", O_RDONLY);
			if (fd == -1)
				free_perror_exit(data, "/dev/null", EXIT_FAILURE);
		}
		if (dup2(fd, STDIN_FILENO) == -1)
			free_perror_exit(data, "dup2", EXIT_FAILURE);
		if (close(fd) == -1)
			free_perror_exit(data, "close", EXIT_FAILURE);
	}
	else
	{
		if (dup2(process->pipe_read_fd, STDIN_FILENO) == -1)
			free_perror_exit(data, "dup2", EXIT_FAILURE);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	*data;
	pid_t	pid;
	int		i;

	if (argc < 5)
		return (EXIT_FAILURE);
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
				free_perror_exit(data, "pipes_close", EXIT_FAILURE);
			process_execute(data, command_create(data, data->processes[i]));
		}
		data->processes_active++;
		i++;
	}
	return (pipex_cleanup(data));
}
