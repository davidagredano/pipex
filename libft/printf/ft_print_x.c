/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 23:31:57 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/12 23:31:58 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "../libft.h"

/**
 * Ignores '#' if the conversion is "0" or "", which means that the input was 0.
 * Ignores '0' flag if left justification or precision is given.
 * Resets the unsupported ' ' and '+' flags.
 * Ensures a minimum precision and field width to avoid truncation,
 * adding extra space if '#' flag is present.
 */
static void	ft_validate_spec(char *conv, t_spec *spec)
{
	if (ft_strncmp(conv, "0", 2) == 0 || ft_strncmp(conv, "", 1) == 0)
		spec->alternative_form = false;
	if (spec->left_align || spec->precision >= 0)
		spec->zero_padding = false;
	spec->leading_blank = false;
	spec->leading_sign = '\0';
	if (spec->precision < (int) ft_strlen(conv))
		spec->precision = ft_strlen(conv);
	if (spec->alternative_form)
		spec->precision += 2;
	if (spec->field_width < spec->precision)
		spec->field_width = spec->precision;
}

/**
 * The unsigned int argument is converted to unsigned hexadecimal notation.
 * The letters abcdef are used for 'x' conversions;
 * the letters ABCDEF are used for 'X' conversions.
 * The precision, if any, gives the minimum number of digits that must appear;
 * if the converted value requires fewer digits, it is padded on the left
 * with zeros.
 * When 0 is printed with an explicit precision 0, the output is empty.
 * Flags admitted: alternative form, zero padding, left justification,
 * field width, precision.
 */
int	ft_print_x(unsigned n, t_spec *spec)
{
	char	*str;
	char	*conv;
	int		chars_printed;

	if (n == 0 && spec->precision == 0)
		conv = ft_strdup("");
	else if (spec->specifier == 'x')
		conv = ft_uitoa(n, 16);
	else
		conv = ft_uitoa_caps(n, 16);
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
