/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:54:46 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/11 17:54:48 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"
#include "../libft/libft.h"

void	heredoc_free(t_hdoc *heredoc)
{
	if (heredoc->filename)
		free(heredoc->filename);
	free(heredoc);
}

static int	heredoc_read_stdin(t_hdoc *heredoc)
{
	int		fd;
	char	*line;

	fd = open(heredoc->filename, O_CREAT | O_WRONLY, 0600);
	if (fd == -1)
		return (-1);
	ft_putstr_fd("> ", STDOUT_FILENO);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			return (-1);
		ft_strtok(line, "\n");
		if (ft_strcmp(line, heredoc->limiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
		ft_putstr_fd("> ", STDOUT_FILENO);
	}
	if (close(fd) == -1)
		return (-1);
	return (0);
}

int	heredoc_init(t_hdoc *heredoc, char *argv[])
{
	char	*filename;
	int		i;

	heredoc->limiter = argv[2];
	i = 0;
	while (1)
	{
		filename = ft_itoa(i);
		if (filename == NULL)
			return (-1);
		if (access(filename, F_OK) == -1)
		{
			heredoc->filename = filename;
			break ;
		}
		free(filename);
		i++;
	}
	if (heredoc_read_stdin(heredoc) == -1)
		return (-1);
	return (0);
}

t_hdoc	*heredoc_create(void)
{
	t_hdoc	*heredoc;

	heredoc = (t_hdoc *) ft_calloc(1, sizeof(t_hdoc));
	if (!heredoc)
		return (NULL);
	return (heredoc);
}
