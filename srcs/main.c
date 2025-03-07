/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:53:33 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/07 13:58:22 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_cmd	*cmd;
	int		pipefd[2];
	int		fd;
	pid_t	pid[2];
	int		wstatus;

	if (argc != 5)
		return (EXIT_FAILURE);
	pipe(pipefd);
	pid[0] = fork();
	if (pid[0] == 0)
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
		if (execve(cmd->filename, cmd->argv, cmd->envp) == -1)
		{
			// If execve fail, print error and manually free memory
			dprintf(STDERR_FILENO, "%s: command not found\n", argv[2]);
			cmd_free(cmd);
			exit(EXIT_COMMAND_NOT_FOUND);
		}
	}
	pid[1] = fork();
	if (pid[1] == 0)
	{
		cmd = cmd_process(argv[3], envp);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		fd = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd == -1)
		{
			// If outfile open fail, exit this process
			perror(argv[4]);
			cmd_free(cmd);
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
		close(pipefd[1]);
		// Execute the command
		if (execve(cmd->filename, cmd->argv, cmd->envp) == -1)
		{
			// If execve fail, print error and manually free memory
			dprintf(STDERR_FILENO, "%s: command not found\n", argv[3]);
			cmd_free(cmd);
			exit(EXIT_COMMAND_NOT_FOUND);
		}
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], &wstatus, 0);
	// Return the last command status code if it terminated normally.
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	return (EXIT_FAILURE);
}
