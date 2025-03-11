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
	int	*pipe;
	int	ret;

	ret = 0;
	ptr = pipes;
	while (*ptr)
	{
		pipe = *ptr;
		if (pipe[0] != -1)
		{
			if (close(pipe[0]) == -1)
				ret = -1;
		}
		if (pipe[1] != -1)
		{
			if (close(pipe[1]) == -1)
				ret = -1;
		}
		ptr++;
	}
	return (ret);
}

int	**pipes_create(int count)
{
	int	**pipes;
	int	i;

	pipes = (int **) ft_calloc(count + 1, sizeof(int *));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < count)
	{
		pipes[i] = (int *) ft_calloc(2, sizeof(int));
		if (!pipes[i])
		{
			pipes_free(pipes);
			return (NULL);
		}
		if (pipe(pipes[i]) == -1)
		{
			pipes_free(pipes);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}
