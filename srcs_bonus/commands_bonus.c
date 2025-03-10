/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:40:31 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/10 18:27:52 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"
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

static char	**get_path_strs(char **envp)
{
	char	**env_ptr;

	env_ptr = envp;
	while (*env_ptr)
	{
		if (ft_strncmp(*env_ptr, "PATH=", 5) == 0)
			return (ft_split(*env_ptr + 5, ':'));
		env_ptr++;
	}
	return (NULL);
}

char	*cmd_get_filename(char *cmd_name, char **envp)
{
	char	**path_strs;
	char	**path_ptr;
	char	*candidate;

	if (access(cmd_name, X_OK) == 0)
		return (ft_strdup(cmd_name));
	path_strs = get_path_strs(envp);
	if (!path_strs)
		return (NULL);
	path_ptr = path_strs;
	while (*path_ptr)
	{
		candidate = path_join(*path_ptr, cmd_name);
		if (!candidate)
			break ;
		else if (access(candidate, X_OK) == 0)
			break ;
		free(candidate);
		path_ptr++;
	}
	if (*path_ptr == NULL)
		candidate = ft_strdup("command not found");
	free_strs(path_strs);
	return (candidate);
}
