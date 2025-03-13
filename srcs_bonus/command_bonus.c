/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:40:31 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/13 00:01:12 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"
#include "../libft/libft.h"

void	command_free(t_cmd *command)
{
	char	**ptr;

	if (!command)
		return ;
	if (command->filename)
		free(command->filename);
	if (command->argv)
	{
		ptr = command->argv;
		while (*ptr)
		{
			free(*ptr);
			ptr++;
		}
		free(command->argv);
	}
	free(command);
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

static char	*command_get_filename(char *command_name, char **envp)
{
	char	**path_strs;
	char	**path_ptr;
	char	*candidate;

	if (ft_strchr(command_name, '/') && access(command_name, X_OK) == 0)
		return (ft_strdup(command_name));
	path_strs = get_path_strs(envp);
	if (!path_strs)
		return (NULL);
	path_ptr = path_strs;
	while (*path_ptr)
	{
		candidate = path_join(*path_ptr, command_name);
		if (!candidate)
			break ;
		else if (access(candidate, X_OK) == 0)
			break ;
		free(candidate);
		path_ptr++;
	}
	if (*path_ptr == NULL)
		candidate = ft_strdup("command not found");
	strs_free(path_strs);
	return (candidate);
}

t_cmd	*command_create(t_pipex *data, t_proc *process)
{
	t_cmd	*command;

	command = (t_cmd *) ft_calloc(1, sizeof(t_cmd));
	if (!command)
		cleanup_exit(data, "command_create", EXIT_FAILURE);
	command->argv = ft_split(process->command_str, ' ');
	if (!command->argv)
	{
		command_free(command);
		cleanup_exit(data, "command_create", EXIT_FAILURE);
	}
	command->filename = command_get_filename(command->argv[0], data->envp);
	if (!command->filename)
	{
		command_free(command);
		cleanup_exit(data, "command_create", EXIT_FAILURE);
	}
	if (ft_strcmp(command->filename, "command not found") == 0)
	{
		print_error(process->command_str, ": command not found\n");
		command_free(command);
		pipex_free(data);
		exit(EXIT_COMMAND_NOT_FOUND);
	}
	return (command);
}
