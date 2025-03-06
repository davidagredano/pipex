/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:53:33 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/06 14:36:00 by dagredan         ###   ########.fr       */
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
	if (access(argv[1], R_OK) == -1)
	{
		perror(argv[1]);
		return (EXIT_FAILURE);
	}
	pipe(pipefd);
	if (fork() == 0)
	{
		cmd = cmd_process(argv[2], envp);
		close(pipefd[0]);
		fd = open(argv[1], O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
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
