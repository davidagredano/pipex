/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:29:31 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/14 09:52:36 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../libft/libft.h"

int	pipes_destroy(t_pipex *data)
{
	int	**pipes_ptr;
	int	*pipe_fd;
	int	return_value;

	if (!data->pipes)
		return (0);
	return_value = 0;
	pipes_ptr = data->pipes;
	while (*pipes_ptr)
	{
		pipe_fd = *pipes_ptr;
		if (close(pipe_fd[0]) == -1)
			return_value = -1;
		if (close(pipe_fd[1]) == -1)
			return_value = -1;
		free(pipe_fd);
		pipes_ptr++;
	}
	free(data->pipes);
	data->pipes = NULL;
	return (return_value);
}

void	pipes_create(t_pipex *data, int count)
{
	int	i;

	data->pipes = (int **) ft_calloc(count + 1, sizeof(int *));
	if (!data->pipes)
		parent_cleanup_exit(data, "pipes_create");
	i = 0;
	while (i < count)
	{
		data->pipes[i] = (int *) ft_calloc(2, sizeof(int));
		if (!data->pipes[i])
			parent_cleanup_exit(data, "pipes_create");
		if (pipe(data->pipes[i]) == -1)
		{
			free(data->pipes[i]);
			parent_cleanup_exit(data, "pipes_create");
		}
		i++;
	}
}
