/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_dirs_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 21:28:31 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/18 22:26:18 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"
#include "../libft/libft.h"

void	path_dirs_free(char **path_dirs)
{
	char	**ptr;

	ptr = path_dirs;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(path_dirs);
}

void	path_dirs_create(t_pipex *data, char **envp)
{
	char	**ptr;

	ptr = envp;
	while (ptr && *ptr)
	{
		if (ft_strncmp(*ptr, "PATH=", 5) == 0)
		{
			data->path_dirs = ft_split(*ptr + 5, ':');
			if (!data->path_dirs)
				parent_cleanup_exit(data, "path_dirs_create");
			return ;
		}
		ptr++;
	}
	data->path_dirs = ft_split(DEF_PATH, ':');
	if (!data->path_dirs)
		parent_cleanup_exit(data, "path_dirs_create");
}
