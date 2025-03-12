/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 23:32:01 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/12 23:32:04 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "../libft.h"

static int	ft_print_format(t_spec *spec, va_list ap)
{
	if (spec->specifier == 'c')
		return (ft_print_c(va_arg(ap, int), spec));
	else if (spec->specifier == 's')
		return (ft_print_s(va_arg(ap, const char *), spec));
	else if (spec->specifier == 'p')
		return (ft_print_p(va_arg(ap, void *), spec));
	else if (spec->specifier == 'd' || spec->specifier == 'i')
		return (ft_print_d(va_arg(ap, int), spec));
	else if (spec->specifier == 'u')
		return (ft_print_u(va_arg(ap, unsigned), spec));
	else if (spec->specifier == 'x' || spec->specifier == 'X')
		return (ft_print_x(va_arg(ap, unsigned), spec));
	else if (spec->specifier == '%')
		return (ft_putchar('%'));
	return (0);
}

static int	ft_print_format_str(char const *format, va_list ap, t_spec *spec)
{
	size_t	i;
	int		chars_printed;
	int		print_return;

	chars_printed = 0;
	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%' && ft_isvalid(&format[i + 1]))
		{
			i += 1 + ft_parse(&format[i + 1], spec);
			print_return = ft_print_format(spec, ap);
		}
		else
		{
			print_return = ft_putchar(format[i]);
		}
		if (print_return == -1)
			return (-1);
		chars_printed += print_return;
		i++;
	}
	return (chars_printed);
}

int	ft_printf(char const *format, ...)
{
	va_list	ap;
	t_spec	*spec;
	int		chars_printed;

	spec = ft_calloc(1, sizeof(t_spec));
	if (!spec)
		return (-1);
	va_start(ap, format);
	chars_printed = ft_print_format_str(format, ap, spec);
	va_end(ap);
	free(spec);
	return (chars_printed);
}
