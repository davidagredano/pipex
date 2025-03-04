/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:53:33 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/04 16:33:27 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	file_set_to_fd(char *file, int flags, int mode, int target_fd)
{
	int	fd;

	fd = open(file, flags, mode);
	if (fd == -1)
		exit(EXIT_FAILURE);
	dup2(fd, target_fd);
	close(fd);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_cmd	*cmd1;
	t_cmd	*cmd2;

	if (argc != 5)
		return (EXIT_FAILURE);
	if (access(argv[1], R_OK) == -1)
	{
		perror(argv[1]);
		return (EXIT_FAILURE);
	}
	file_set_to_fd(argv[1], O_RDONLY, 0, STDIN_FILENO);
	file_set_to_fd(argv[4], O_CREAT | O_TRUNC | O_WRONLY, 0644, STDOUT_FILENO);
	cmd1 = cmd_process(argv[2], envp);
	cmd2 = cmd_process(argv[3], envp);
	cmd_exec(cmd1);
	cmd_exec(cmd2);
	cmd_free(cmd1);
	cmd_free(cmd2);
}
