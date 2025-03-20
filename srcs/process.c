/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:21:25 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/20 21:15:06 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	process_execute(t_pipex *data, t_proc *process)
{
	t_cmd	*command;
	char	*command_str;

	command = process->command;
	if (execve(command->filename, command->argv, data->envp) == -1)
	{
		command_str = process->command_str;
		if (access(command->filename, F_OK) == -1)
			child_cleanup_exit(data, command_str, EXIT_COMMAND_NOT_FOUND);
		else if (access(command->filename, X_OK) == -1)
			child_cleanup_exit(data, command->filename, EXIT_PERMISSION_DENIED);
		child_cleanup_exit(data, command_str, EXIT_FAILURE);
	}
}

void	process_redirect_stdout(t_pipex *data, t_proc *process)
{
	int	fd;

	if (process->outfile)
	{
		fd = open(process->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd == -1)
			child_cleanup_exit(data, process->outfile, EXIT_FAILURE);
		if (dup2(fd, STDOUT_FILENO) == -1)
			child_cleanup_exit(data, "process_redirect_stdout", EXIT_FAILURE);
		if (close(fd) == -1)
			child_cleanup_exit(data, "process_redirect_stdout", EXIT_FAILURE);
	}
	else
	{
		if (dup2(process->pipe_write_fd, STDOUT_FILENO) == -1)
			child_cleanup_exit(data, "process_redirect_stdout", EXIT_FAILURE);
	}
}

void	process_redirect_stdin(t_pipex *data, t_proc *process)
{
	int	fd;

	if (process->infile)
	{
		fd = open(process->infile, O_RDONLY);
		if (fd == -1)
		{
			perror(process->infile);
			fd = open("/dev/null", O_RDONLY);
			if (fd == -1)
				child_cleanup_exit(data, "/dev/null", EXIT_FAILURE);
		}
		if (dup2(fd, STDIN_FILENO) == -1)
			child_cleanup_exit(data, "process_redirect_stdin", EXIT_FAILURE);
		if (close(fd) == -1)
			child_cleanup_exit(data, "process_redirect_stdin", EXIT_FAILURE);
	}
	else
	{
		if (dup2(process->pipe_read_fd, STDIN_FILENO) == -1)
			child_cleanup_exit(data, "process_redirect_stdin", EXIT_FAILURE);
	}
}
