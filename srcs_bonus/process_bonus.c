/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:21:25 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/12 14:21:26 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	process_execute(t_pipex *data, t_cmd *command)
{
	if (execve(command->filename, command->argv, data->envp) == -1)
	{
		command_free(command);
		process_perror_free_exit("execve", data, EXIT_FAILURE);
	}
}

void	process_redirect_stdout(t_pipex *data, t_proc *process)
{
	int	fd;

	if (process->outfile)
	{
		if (data->heredoc_enabled)
			fd = open(process->outfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
		else
			fd = open(process->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd == -1)
			process_perror_free_exit(process->outfile, data, EXIT_FAILURE);
		if (dup2(fd, STDOUT_FILENO) == -1)
			process_perror_free_exit("dup2", data, EXIT_FAILURE);
		if (close(fd) == -1)
			process_perror_free_exit("close", data, EXIT_FAILURE);
	}
	else
	{
		if (dup2(process->pipe_write_fd, STDOUT_FILENO) == -1)
			process_perror_free_exit("dup2", data, EXIT_FAILURE);
	}
}

void	process_redirect_stdin(t_pipex *data, t_proc *process)
{
	int	fd;

	if (process->infile)
	{
		fd = open(process->infile, O_RDONLY);
		if (fd != -1 && data->heredoc_enabled && unlink(process->infile) == -1)
			process_perror_free_exit("unlink", data, EXIT_FAILURE);
		if (fd == -1)
		{
			perror(process->infile);
			fd = open("/dev/null", O_RDONLY);
			if (fd == -1)
				process_perror_free_exit("/dev/null", data, EXIT_FAILURE);
		}
		if (dup2(fd, STDIN_FILENO) == -1)
			process_perror_free_exit("dup2", data, EXIT_FAILURE);
		if (close(fd) == -1)
			process_perror_free_exit("close", data, EXIT_FAILURE);
	}
	else
	{
		if (dup2(process->pipe_read_fd, STDIN_FILENO) == -1)
			process_perror_free_exit("dup2", data, EXIT_FAILURE);
	}
}
