/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:13:03 by dagredan          #+#    #+#             */
/*   Updated: 2025/02/21 13:39:50 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Extracts everything after the newline character as remainder.
 * Ends line by putting a NUL character after the newline character.
 */
static char	*clean_line(char *line)
{
	char	*remainder;

	remainder = ft_strdup(ft_strchr(line, '\n') + 1);
	if (!remainder)
	{
		free(line);
		line = NULL;
		return (NULL);
	}
	if (remainder[0] == '\0')
	{
		free(remainder);
		remainder = NULL;
	}
	line[ft_strchr(line, '\n') - line + 1] = '\0';
	return (remainder);
}

/**
 * Concatenates the buffer of characters read to line.
 * Allocates a new string combining the two and frees the previous one.
 */
static char	*extend_line(char *line, char *buf)
{
	char	*new_line;
	int		memsize;

	memsize = ft_strlen(line) + ft_strlen(buf) + 1;
	new_line = (char *) malloc(memsize * sizeof(char));
	if (!new_line)
	{
		free(line);
		return (NULL);
	}
	ft_strlcpy(new_line, line, memsize);
	ft_strlcpy(new_line + ft_strlen(line), buf, memsize - ft_strlen(line));
	free(line);
	return (new_line);
}

/**
 * Reads the file until a newline character is found or until the end of file.
 * Adds all characters read to line.
 */
static char	*feed_line(char *line, int fd)
{
	char		*buf;
	ssize_t		n;

	buf = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
	{
		free(line);
		return (NULL);
	}
	n = 1;
	while (n > 0 && line && !ft_strchr(line, '\n'))
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n == -1 || (n == 0 && line[0] == '\0'))
		{
			free(line);
			free(buf);
			return (NULL);
		}
		buf[n] = '\0';
		line = extend_line(line, buf);
	}
	free(buf);
	return (line);
}

/**
 * Puts the remainder from the previous call in line.
 * If there was no remainder (it is the first call or it is a call after EOF),
 * initializes line with an empty string.
 */
static char	*init_line(char *remainder)
{
	char		*line;

	line = remainder;
	if (!line)
		line = ft_strdup("");
	return (line);
}

/**
 * Returns the next line of the file descriptor.
 * If a complete line is found in the remainder, it is returned from there.
 * Otherwise, it reads the file until a complete line is found.
 * Before returning the line, it saves the remainder for later calls.
 */
char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = init_line(remainder);
	remainder = NULL;
	if (line && !ft_strchr(line, '\n'))
		line = feed_line(line, fd);
	if (line && ft_strchr(line, '\n'))
		remainder = clean_line(line);
	return (line);
}
