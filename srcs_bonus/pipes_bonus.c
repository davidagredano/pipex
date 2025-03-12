/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:29:31 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/11 14:54:38 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"
#include "../libft/libft.h"

void	pipes_free(int **pipes)
{
	int	**ptr;

	ptr = pipes;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(pipes);
}

int	pipes_close(int **pipes)
{
	int	**ptr;
	int	ret;

	ret = 0;
	if (!pipes)
		return (ret);
	ptr = pipes;
	while (*ptr)
	{
		if ((*ptr)[0] != -1)
		{
			if (close((*ptr)[0]) == -1)
				ret = -1;
		}
		if ((*ptr)[1] != -1)
		{
			if (close((*ptr)[1]) == -1)
				ret = -1;
		}
		ptr++;
	}
	if (ret == -1)
		pipes_free(pipes);
	return (ret);
}

void	pipes_create(t_pipex *data, int count)
{
	int	i;

	data->pipes = (int **) ft_calloc(count + 1, sizeof(int *));
	if (!data->pipes)
		cleanup_exit(data, "pipes_create", EXIT_FAILURE);
	i = 0;
	while (i < count)
	{
		data->pipes[i] = (int *) ft_calloc(2, sizeof(int));
		if (!data->pipes[i])
			cleanup_exit(data, "pipes_create", EXIT_FAILURE);
		if (pipe(data->pipes[i]) == -1)
		{
			free(data->pipes[i]);
			cleanup_exit(data, "pipes_create", EXIT_FAILURE);
		}
		i++;
	}
}
