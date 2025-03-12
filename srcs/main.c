/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:53:33 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/12 23:59:58 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	int		pipefd[2];
	pid_t	pid;
	int		last_exit_status;

	if (argc != 5)
		return (EXIT_FAILURE);
	if (pipe(pipefd) == -1)
		perror_exit("pipe", EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		perror_exit("fork", EXIT_FAILURE);
	else if (pid == 0)
		process_child1(pipefd, argv[1], argv[2], envp);
	pid = fork();
	if (pid == -1)
	{
		cleanup_partial(pipefd);
		perror_exit("fork", EXIT_FAILURE);
	}
	else if (pid == 0)
		process_child2(pipefd, argv[4], argv[3], envp);
	last_exit_status = cleanup(pipefd);
	if (WIFEXITED(last_exit_status))
		return (WEXITSTATUS(last_exit_status));
	return (EXIT_FAILURE);
}
