/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:40:31 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/18 22:21:59 by dagredan         ###   ########.fr       */
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

static char	*command_get_filename(t_pipex *data, char *command_name)
{
	char	**path_ptr;
	char	*candidate;

	if (ft_strchr(command_name, '/') && access(command_name, F_OK) == 0)
		return (ft_strdup(command_name));
	path_ptr = data->path_dirs;
	while (*path_ptr)
	{
		candidate = path_join(*path_ptr, command_name);
		if (!candidate)
			break ;
		else if (access(candidate, F_OK) == 0)
			break ;
		free(candidate);
		path_ptr++;
	}
	if (*path_ptr == NULL)
		candidate = ft_strdup(command_name);
	return (candidate);
}

void	command_create(t_pipex *data, t_proc *process)
{
	t_cmd	*command;

	if (ft_strcmp(process->command_str, "") == 0)
		child_cleanup_exit(data, "", EXIT_COMMAND_NOT_FOUND);
	command = (t_cmd *) ft_calloc(1, sizeof(t_cmd));
	if (!command)
		child_cleanup_exit(data, "command_create", EXIT_FAILURE);
	process->command = command;
	command->argv = ft_split(process->command_str, ' ');
	if (!command->argv)
		child_cleanup_exit(data, "command_create", EXIT_FAILURE);
	command->filename = command_get_filename(data, command->argv[0]);
	if (!command->filename)
		child_cleanup_exit(data, "command_create", EXIT_FAILURE);
}
