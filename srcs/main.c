/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:53:33 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/07 17:45:48 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../libft/libft.h"

static void	process_execute(t_cmd *cmd)
{
	if (execve(cmd->filename, cmd->argv, cmd->envp) == -1)
	{
		cmd_free(cmd);
		exit(EXIT_FAILURE);
	}
}

static t_cmd	*cmd_create(char *cmd_str, char **envp)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		exit(EXIT_FAILURE);
	cmd->envp = envp;
	cmd->argv = ft_split(cmd_str, ' ');
	if (!cmd->argv)
	{
		cmd_free(cmd);
		exit(EXIT_FAILURE);
	}
	cmd->filename = cmd_get_filename(cmd->argv[0], envp);
	if (!cmd->filename)
	{
		cmd_free(cmd);
		exit(EXIT_FAILURE);
	}
	if (ft_strcmp(cmd->filename, "command not found") == 0)
	{
		dprintf(STDERR_FILENO, "%s: command not found\n", cmd->argv[0]);
		cmd_free(cmd);
		exit(EXIT_COMMAND_NOT_FOUND);
	}
	return (cmd);
}

static void	process_redirect_stdout(int pipe[2], char *outfile)
{
	int	fd;

	if (outfile)
	{
		fd = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd == -1)
		{
			perror(outfile);
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else
		dup2(pipe[1], STDOUT_FILENO);
	close(pipe[1]);
}

static void	process_redirect_stdin(int pipe[2], char *infile)
{
	int	fd;

	if (infile)
	{
		fd = open(infile, O_RDONLY);
		if (fd == -1)
		{
			perror(infile);
			fd = open("/dev/null", O_RDONLY);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else
		dup2(pipe[0], STDIN_FILENO);
	close(pipe[0]);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		pipefd[2];
	pid_t	pids[2];
	int		last_exit_status;

	if (argc != 5)
		return (EXIT_FAILURE);
	pipe(pipefd);
	pids[0] = fork();
	if (pids[0] == 0)
	{
		process_redirect_stdin(pipefd, argv[1]);
		process_redirect_stdout(pipefd, NULL);
		process_execute(cmd_create(argv[2], envp));
	}
	pids[1] = fork();
	if (pids[1] == 0)
	{
		process_redirect_stdin(pipefd, NULL);
		process_redirect_stdout(pipefd, argv[4]);
		process_execute(cmd_create(argv[3], envp));
	}
	last_exit_status = cleanup(pipefd, pids);
	if (WIFEXITED(last_exit_status))
		return (WEXITSTATUS(last_exit_status));
	return (EXIT_FAILURE);
}
