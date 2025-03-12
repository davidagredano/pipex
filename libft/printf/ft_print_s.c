/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 23:31:48 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/12 23:31:51 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "../libft.h"

/**
 * Copies the string src, properly aligned, to the buffer pointed to by dst.
 */
static void	ft_insert_str(char *dst, const char *src, t_spec *spec)
{
	int	i;

	i = 0;
	if (spec->left_align)
	{
		while (i < spec->precision)
		{
			dst[i] = src[i];
			i++;
		}
	}
	else
	{
		i = spec->field_width - spec->precision;
		ft_strlcpy(dst + i, src, spec->precision + 1);
	}
}

/**
 * Ignores not used flags for this spec.
 * If a precision is given, no NUL byte needs to be present; if the precision
 * is not specified, or is greater than the size of the string, the string must
 * contain a terminating NUL byte.
 * Ensures a minimum precision and field width to avoid truncation.
 */
static void	ft_validate_spec(const char *s, t_spec *spec)
{
	spec->alternative_form = false;
	spec->zero_padding = false;
	spec->leading_blank = false;
	spec->leading_sign = false;
	if (spec->precision >= 0)
		spec->precision = ft_strnlen(s, spec->precision);
	else
		spec->precision = ft_strlen(s);
	if (spec->field_width < spec->precision)
		spec->field_width = spec->precision;
}

/**
 * The characters of the string are written up to the NUL byte;
 * if a precision is specified, no more than the number specified are written.
 * Flags admitted: left justification, field width, precision.
 */
int	ft_print_s(const char *s, t_spec *spec)
{
	char	*str;
	int		chars_printed;

	if (!s && spec->precision > -1 && spec->precision < 6)
		s = "";
	else if (!s)
		s = "(null)";
	ft_validate_spec(s, spec);
	str = ft_get_base_str(spec);
	if (!str)
		return (-1);
	ft_insert_str(str, s, spec);
	chars_printed = ft_putstr(str);
	free(str);
	return (chars_printed);
}
