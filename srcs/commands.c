/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:28:06 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/04 13:09:03 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../libft/libft.h"

void	cmd_exec(t_cmd *cmd)
{
	if (execve(cmd->filename, cmd->argv, cmd->envp) == -1)
		cmd_exit_error(cmd, "Command execution failed");
}

t_cmd	*cmd_process(char *cmd_str, char **envp)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		cmd_exit_error(cmd, "Command struct allocation failed");
	cmd->envp = envp;
	cmd->argv = ft_split(cmd_str, ' ');
	if (!cmd->argv)
		cmd_exit_error(cmd, "Error during cmd->argv allocation");
	cmd->filename = cmd_get_filename(cmd);
	if (!cmd->filename)
		cmd_exit_error(cmd, "Error during cmd->filename allocation");
	return (cmd);
}
