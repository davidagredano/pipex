/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:55:40 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/12 23:59:36 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	process_execute(t_cmd *command)
{
	if (!command)
		perror_exit("command_create", EXIT_FAILURE);
	if (execve(command->filename, command->argv, command->envp) == -1)
	{
		command_free(command);
		perror_exit("execve", EXIT_FAILURE);
	}
}

void	process_redirect_stdout(int pipe[2], char *outfile)
{
	int	fd;

	if (outfile)
	{
		fd = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd == -1)
			perror_exit(outfile, EXIT_FAILURE);
		if (dup2(fd, STDOUT_FILENO) == -1)
			perror_exit("dup2", EXIT_FAILURE);
		if (close(fd) == -1)
			perror_exit("close", EXIT_FAILURE);
	}
	else
	{
		if (dup2(pipe[1], STDOUT_FILENO) == -1)
			perror_exit("dup2", EXIT_FAILURE);
	}
	if (close(pipe[1]) == -1)
		perror_exit("close", EXIT_FAILURE);
}

void	process_redirect_stdin(int pipe[2], char *infile)
{
	int	fd;

	if (infile)
	{
		fd = open(infile, O_RDONLY);
		if (fd == -1)
		{
			perror(infile);
			fd = open("/dev/null", O_RDONLY);
			if (fd == -1)
				perror_exit("/dev/null", EXIT_FAILURE);
		}
		if (dup2(fd, STDIN_FILENO) == -1)
			perror_exit("dup2", EXIT_FAILURE);
		if (close(fd) == -1)
			perror_exit("close", EXIT_FAILURE);
	}
	else
	{
		if (dup2(pipe[0], STDIN_FILENO) == -1)
			perror_exit("dup2", EXIT_FAILURE);
	}
	if (close(pipe[0]) == -1)
		perror_exit("close", EXIT_FAILURE);
}

void	process_child2(int pipe[2], char *outfile, char *cmd_str, char *envp[])
{
	process_redirect_stdin(pipe, NULL);
	process_redirect_stdout(pipe, outfile);
	process_execute(command_create(cmd_str, envp));
}

void	process_child1(int pipe[2], char *infile, char *cmd_str, char *envp[])
{
	process_redirect_stdin(pipe, infile);
	process_redirect_stdout(pipe, NULL);
	process_execute(command_create(cmd_str, envp));
}
