/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:28:06 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/06 17:54:02 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../libft/libft.h"

static void	file_set_fd(char *file, int flags, int mode, int target_fd)
{
	int	fd;

	fd = open(file, flags, mode);
	if (fd == -1)
		exit(EXIT_FAILURE);
	dup2(fd, target_fd);
	close(fd);
}

void	cmd_exec(t_cmd *cmd, char *infile, char *outfile)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		cmd_exit_error(cmd, "fork");
	if (pid == 0)
	{
		file_set_fd(infile, O_RDONLY, 0, STDIN_FILENO);
		file_set_fd(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0644, STDOUT_FILENO);
		if (execve(cmd->filename, cmd->argv, cmd->envp) == -1)
			cmd_exit_error(cmd, "execve");
	}
	else
		wait(NULL);
}

t_cmd	*cmd_process(char *cmd_str, char **envp)
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
	cmd->filename = cmd_get_filename(cmd);
	if (!cmd->filename)
		cmd->filename = ft_strdup(cmd_str);
	if (!cmd->filename)
	{
		cmd_free(cmd);
		exit(EXIT_FAILURE);
	}
	return (cmd);
}
