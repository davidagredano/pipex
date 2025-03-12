/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:53:33 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/11 14:54:19 by dagredan         ###   ########.fr       */
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

static t_cmd	*cmd_create(t_pipex *data, t_proc *process)
{
	t_cmd	*cmd;

	cmd = (t_cmd *) ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		free_perror_exit(data, "cmd_create", EXIT_FAILURE);
	cmd->argv = ft_split(process->cmd_str, ' ');
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
		if (data->heredoc_enabled)
			fd = open(process->outfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
		else
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
	int		i;

	if (argc < 5)
		return (EXIT_FAILURE);
	data = pipex_create(argc, argv, envp);
	i = 0;
	while (i < data->processes_count)
	{
		pid = fork();
		if (pid == -1)
			pipex_perror_cleanup_exit("fork", data, EXIT_FAILURE);
		else if (pid == 0)
		{
			process_redirect_stdin(data, data->processes[i]);
			process_redirect_stdout(data, data->processes[i]);
			if (pipes_close(data->pipes) == -1)
				free_perror_exit(data, "pipes_close", EXIT_FAILURE);
			process_execute(data, cmd_create(data, data->processes[i]));
		}
		data->active_child_processes++;
		i++;
	}
	return (pipex_cleanup(data));
}
