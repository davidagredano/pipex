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

void	heredoc_read_stdin(t_pipex *data)
{
	int		fd;
	char	*line;

	fd = open(data->heredoc->filename, O_CREAT | O_WRONLY, 0600);
	if (fd == -1)
		cleanup_exit(data, "heredoc_read_stdin", EXIT_FAILURE);
	ft_putstr_fd("> ", STDOUT_FILENO);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			cleanup_exit(data, "heredoc_read_stdin", EXIT_FAILURE);
		ft_strtok(line, "\n");
		if (ft_strcmp(line, data->heredoc->limiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
		ft_putstr_fd("> ", STDOUT_FILENO);
	}
	if (close(fd) == -1)
		cleanup_exit(data, "heredoc_read_stdin", EXIT_FAILURE);
}

void	heredoc_init(t_pipex *data, char *argv[])
{
	char	*filename;
	int		i;

	data->heredoc->limiter = argv[2];
	i = 0;
	while (1)
	{
		filename = ft_itoa(i);
		if (filename == NULL)
			cleanup_exit(data, "heredoc_init", EXIT_FAILURE);
		if (access(filename, F_OK) == -1)
		{
			data->heredoc->filename = filename;
			break ;
		}
		free(filename);
		i++;
	}
}

void	heredoc_create(t_pipex *data, int is_here_doc)
{
	if (!is_here_doc)
		return ;
	data->heredoc_enabled = is_here_doc;
	data->heredoc = (t_hdoc *)ft_calloc(1, sizeof(t_hdoc));
	if (!data->heredoc)
		cleanup_exit(data, "heredoc_create", EXIT_FAILURE);
}
