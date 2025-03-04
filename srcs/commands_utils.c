/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:40:31 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/04 13:04:20 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../libft/libft.h"

void	cmd_free(t_cmd *cmd)
{
	char	**ptr;

	if (!cmd)
		return ;
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

void	cmd_exit_error(t_cmd *cmd, const char *error_msg)
{
	perror(error_msg);
	cmd_free(cmd);
	exit(EXIT_FAILURE);
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

char	*cmd_get_filename(t_cmd *cmd)
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
