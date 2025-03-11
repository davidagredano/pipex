/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:53:33 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/11 13:18:58 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"
#include "../libft/libft.h"

static void	process_execute(t_pipex *data, t_cmd *cmd)
{
	if (execve(cmd->filename, cmd->argv, data->envp) == -1)
	{
		cmd_free(cmd);
		free_perror_exit(data, "execve", EXIT_FAILURE);
	}
}

static t_cmd	*cmd_create(t_pipex *data, char *cmd_str)
{
	t_cmd	*cmd;

	cmd = (t_cmd *) ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		free_perror_exit(data, "cmd_create", EXIT_FAILURE);
	cmd->argv = ft_split(cmd_str, ' ');
	if (!cmd->argv)
	{
		cmd_free(cmd);
		free_perror_exit(data, "cmd_create", EXIT_FAILURE);
	}
	cmd->filename = cmd_get_filename(cmd->argv[0], data->envp);
	if (!cmd->filename)
	{
		cmd_free(cmd);
		free_perror_exit(data, "cmd_create", EXIT_FAILURE);
	}
	if (ft_strcmp(cmd->filename, "command not found") == 0)
	{
		dprintf(STDERR_FILENO, "%s: command not found\n", cmd->argv[0]);
		cmd_free(cmd);
		pipex_free(data);
		exit(EXIT_COMMAND_NOT_FOUND);
	}
	return (cmd);
}

static void	process_redirect_stdout(t_pipex *data, t_proc *process)
{
	int	fd;

	if (process->outfile)
	{
		fd = open(process->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd == -1)
			free_perror_exit(data, process->outfile, EXIT_FAILURE);
		if (dup2(fd, STDOUT_FILENO) == -1)
			free_perror_exit(data, "dup2", EXIT_FAILURE);
		if (close(fd) == -1)
			free_perror_exit(data, "close", EXIT_FAILURE);
	}
	else
	{
		if (dup2(process->pipe_write_fd, STDOUT_FILENO) == -1)
			free_perror_exit(data, "dup2", EXIT_FAILURE);
	}
}

static void	process_redirect_stdin(t_pipex *data, t_proc *process)
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
				free_perror_exit(data, "/dev/null", EXIT_FAILURE);
		}
		if (dup2(fd, STDIN_FILENO) == -1)
			free_perror_exit(data, "dup2", EXIT_FAILURE);
		if (close(fd) == -1)
			free_perror_exit(data, "close", EXIT_FAILURE);
	}
	else
	{
		if (dup2(process->pipe_read_fd, STDIN_FILENO) == -1)
			free_perror_exit(data, "dup2", EXIT_FAILURE);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	*data;
	pid_t	pid;
	int		last_exit_status;

	if (argc != 5)
		return (EXIT_FAILURE);
	data = pipex_create(argc, argv, envp);

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		pipex_cleanup(data);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		process_redirect_stdin(data, data->processes[0]);
		process_redirect_stdout(data, data->processes[0]);
		if (pipes_close(data) == -1)
			free_perror_exit(data, "pipes_close", EXIT_FAILURE);
		process_execute(data, cmd_create(data, argv[2]));
	}
	data->active_child_processes++;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		pipex_cleanup(data);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		process_redirect_stdin(data, data->processes[1]);
		process_redirect_stdout(data, data->processes[1]);
		if (pipes_close(data) == -1)
			free_perror_exit(data, "pipes_close", EXIT_FAILURE);
		process_execute(data, cmd_create(data, argv[3]));
	}
	data->active_child_processes++;

	last_exit_status = pipex_cleanup(data);
	if (WIFEXITED(last_exit_status))
		return (WEXITSTATUS(last_exit_status));
}
