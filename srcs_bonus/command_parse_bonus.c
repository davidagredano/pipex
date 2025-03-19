/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parse_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:25:29 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/19 18:13:48 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

static void	argv_free(char **argv)
{
	char	**ptr;

	ptr = argv;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(argv);
}

static int	argv_count_args(char *cmd_str, char *delim_wrap, char *wrappers)
{
	int		count;
	char	*ptr;

	count = 0;
	ptr = cmd_str;
	while (*ptr != '\0')
	{
		if (!ft_strchr(delim_wrap, *ptr))
		{
			count++;
			ptr += ft_strcspn(ptr, delim_wrap);
		}
		else if (ft_strchr(wrappers, *ptr))
		{
			count++;
			ptr = ft_strchr(ptr + 1, *ptr) + 1;
		}
		else
			ptr++;
	}
	return (count);
}

static int	argv_populate(char **argv, char *ptr, char *delim_wrap, char *wrap)
{
	int		argv_i;
	char	wrap_char;

	argv_i = 0;
	while (*ptr != '\0')
	{
		if (!ft_strchr(delim_wrap, *ptr))
		{
			argv[argv_i++] = ft_substr(ptr, 0, ft_strcspn(ptr, delim_wrap));
			ptr += ft_strcspn(ptr, delim_wrap);
		}
		else if (ft_strchr(wrap, *ptr))
		{
			wrap_char = *ptr;
			ptr++;
			argv[argv_i++] = ft_substr(ptr, 0, ft_strchr(ptr, wrap_char) - ptr);
			ptr = ft_strchr(ptr, wrap_char) + 1;
		}
		else
			ptr++;
		if (argv_i > 0 && !argv[argv_i - 1])
			return (-1);
	}
	return (0);
}

char	**command_parse_argv(char *cmd_str, char *delim_wrap, char *wrappers)
{
	char	**argv;
	int		count;
	char	*ptr;

	count = argv_count_args(cmd_str, delim_wrap, wrappers);
	argv = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!argv)
		return (NULL);
	ptr = cmd_str;
	if (argv_populate(argv, ptr, delim_wrap, wrappers) == -1)
	{
		argv_free(argv);
		return (NULL);
	}
	return (argv);
}
