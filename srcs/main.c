/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:53:33 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/10 19:54:37 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../libft/libft.h"

static void	process_execute(t_cmd *cmd)
{
	if (!cmd)
		perror_exit("cmd_create", EXIT_FAILURE);
	if (execve(cmd->filename, cmd->argv, cmd->envp) == -1)
	{
		cmd_free(cmd);
		perror_exit("execve", EXIT_FAILURE);
	}
}

static t_cmd	*cmd_create(char *cmd_str, char **envp)
{
	t_cmd	*cmd;

	cmd = (t_cmd *) ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->envp = envp;
	cmd->argv = ft_split(cmd_str, ' ');
	if (!cmd->argv)
	{
		cmd_free(cmd);
		return (NULL);
	}
	cmd->filename = cmd_get_filename(cmd->argv[0], envp);
	if (!cmd->filename)
	{
		cmd_free(cmd);
		return (NULL);
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
	{
		process_redirect_stdin(pipefd, argv[1]);
		process_redirect_stdout(pipefd, NULL);
		process_execute(cmd_create(argv[2], envp));
	}
	pid = fork();
	if (pid == -1)
	{
		cleanup_partial(pipefd);
		perror_exit("fork", EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		process_redirect_stdin(pipefd, NULL);
		process_redirect_stdout(pipefd, argv[4]);
		process_execute(cmd_create(argv[3], envp));
	}
	last_exit_status = cleanup(pipefd);
	if (WIFEXITED(last_exit_status))
		return (WEXITSTATUS(last_exit_status));
}
