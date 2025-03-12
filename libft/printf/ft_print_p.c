/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 23:31:39 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/12 23:31:44 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "../libft.h"

/**
 * Ensures alternative form flag.
 * Handles the NULL pointer special case.
 * Ignores '0' flag if left justification or precision is given.
 * Ignores ' ' if '+' is present.
 * Ensures a minimum precision and field width to avoid truncation,
 * adding extra space if ' ', '+' or '#' flags are present.
 * Finally, if the zero padding flag is still on, expands the precision
 * to the full field width to make room for the zeros.
 */
static void	ft_validate_spec(char *conv, t_spec *spec)
{
	spec->alternative_form = true;
	if (ft_strncmp(conv, "(nil)", 6) == 0)
	{
		spec->alternative_form = false;
		spec->zero_padding = false;
		spec->leading_blank = false;
		spec->leading_sign = '\0';
		spec->precision = ft_strlen(conv);
	}
	if (spec->left_align || spec->precision >= 0)
		spec->zero_padding = false;
	if (spec->leading_sign != '\0')
		spec->leading_blank = false;
	if (spec->precision < (int) ft_strlen(conv))
		spec->precision = ft_strlen(conv);
	if (spec->leading_sign != '\0' || spec->leading_blank)
		spec->precision += 1;
	if (spec->alternative_form)
		spec->precision += 2;
	if (spec->field_width < spec->precision)
		spec->field_width = spec->precision;
	if (spec->zero_padding)
		spec->precision = spec->field_width;
}

/**
 * The void * argument is converted to hexadecimal notation (as if by %#x).
 * Flags admitted: zero padding, left justification, leading blank,
 * leading sign, field width, precision.
 */
int	ft_print_p(void *p, t_spec *spec)
{
	char	*str;
	char	*conv;
	int		chars_printed;

	if (!p)
		conv = ft_strdup("(nil)");
	else
		conv = ft_ultoa((unsigned long) p, 16);
	if (!conv)
		return (-1);
	ft_validate_spec(conv, spec);
	str = ft_get_base_str(spec);
	if (!str)
	{
		free(conv);
		return (-1);
	}
	ft_insert_conv(str, conv, spec);
	chars_printed = ft_putstr(str);
	free(conv);
	free(str);
	return (chars_printed);
}
