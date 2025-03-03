/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:28:06 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/03 17:12:24 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../libft/libft.h"

void	cmd_free(t_cmd *cmd)
{
	char	**ptr;

	if (cmd->filename)
		free(cmd->filename);
	if (cmd->argv)
	{
		ptr = cmd->argv;
		while (*ptr)
		{
			free(*ptr);
			ptr++;
		}
		free(cmd->argv);
	}
	free(cmd);
}

static char	*path_join(char *path, char *filename)
{
	char	*new_str;
	int		mem_size;

	mem_size = ft_strlen(path) + ft_strlen("/") + ft_strlen(filename) + 1;
	new_str = (char *) ft_calloc(mem_size, sizeof(char));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, path, mem_size);
	ft_strlcat(new_str, "/", mem_size);
	ft_strlcat(new_str, filename, mem_size);
	return (new_str);
}

static char	**get_path_substrs(char **envp)
{
	char	**ptr;

	ptr = envp;
	while (*ptr)
	{
		if (ft_strncmp(*ptr, "PATH=", 5) == 0)
			return (ft_split(*ptr + 5, ':'));
		ptr++;
	}
	return (NULL);
}

static char	*cmd_get_filename(t_cmd *cmd)
{
	char	**path_substrs;
	char	**ptr;
	char	*candidate;

	path_substrs = get_path_substrs(cmd->envp);
	if (!path_substrs)
		return (NULL);
	ptr = path_substrs;
	while (*ptr)
	{
		candidate = path_join(*ptr, cmd->argv[0]);
		if (!candidate)
		{
			free_strs(path_substrs);
			return (NULL);
		}
		if (access(candidate, X_OK) == 0)
			break ;
		free(candidate);
		candidate = NULL;
		ptr++;
	}
	free_strs(path_substrs);
	return (candidate);
}

t_cmd	*cmd_process(char *cmd_str, char **envp)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->envp = envp;
	cmd->argv = ft_split(cmd_str, ' ');
	if (!cmd->argv)
	{
		cmd_free(cmd);
		return (NULL);
	}
	cmd->filename = cmd_get_filename(cmd);
	if (!cmd->filename)
	{
		cmd_free(cmd);
		return (NULL);
	}
	return (cmd);
}
