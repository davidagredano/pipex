/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:53:33 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/06 15:48:19 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_cmd	*cmd;
	int		pipefd[2];
	int		fd;
	int		wstatus;

	if (argc != 5)
		return (EXIT_FAILURE);
	pipe(pipefd);
	if (fork() == 0)
	{
		cmd = cmd_process(argv[2], envp);
		// Close read end of pipe not used by this subprocess
		close(pipefd[0]);
		// Try to open infile
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			// If infile open fail, set infile to be /dev/null
			perror(argv[1]);
			fd = open("/dev/null", O_RDONLY);
		}
		// Set the opened file to be the stdin
		dup2(fd, STDIN_FILENO);
		close(fd);
		// Set the write end of the pipe to be the stdout
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		// Execute the command
		execve(cmd->filename, cmd->argv, cmd->envp);
	}
	close(pipefd[1]);
	wait(NULL);
	if (fork() == 0)
	{
		cmd = cmd_process(argv[3], envp);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		fd = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		execve(cmd->filename, cmd->argv, cmd->envp);
	}
	close(pipefd[0]);
	wait(&wstatus);
	// Return the last command status code if it terminated normally.
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	return (EXIT_FAILURE);
}
